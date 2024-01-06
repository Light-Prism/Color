#include "ColorPCH.h"
#include "OpenGLShader.h"

#include "Utils/FileSystem.h"
#include "Utils/Timer.h"

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Color
{
	namespace Utils
	{
		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
			{
				return GL_VERTEX_SHADER;
			}
			else if (type == "fragment" || type == "pixel")
			{
				return GL_FRAGMENT_SHADER;
			}

			checkf(false, "Unknown shader type string!");
			return 0;
		}

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return shaderc_vertex_shader;
			case GL_FRAGMENT_SHADER: return shaderc_fragment_shader;
			}

			unreachable();
			return (shaderc_shader_kind)0;
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}

			unreachable();
			return nullptr;
		}

		static const char* GetCacheDirectory()
		{
			// Not preffered because if the 'Shaders' directory is copied and there are cached shaders, those are copied over as well which may not be the preferred behavior.
			// return "Assets/Shaders/Cache/OpenGL";

			// We use the 'OpenGL' subdirectory at the end because other graphics APIs may have cached their shaders too, this is to stop conflicting shader caches.
			// Each API uses their own subdirectory, DirectX; Vulkan, Metal... etc.
			return "Assets/Cache/Shaders/OpenGL";
		}

		static void CreateCacheDirectoryIfAbsent()
		{
			const char* directory = GetCacheDirectory();

			if (FileSystem::Exists(directory))
			{
				if (FileSystem::IsFile(directory))
					FileSystem::RemoveFile(directory);
			}
			else
			{
				FileSystem::CreateDirRecursive(directory);
			}
		}

		static const char* GLShaderStageGLCachedFileExt(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return ".cached_opengl.vert";
			case GL_FRAGMENT_SHADER: return ".cached_opengl.frag";
			}

			unreachable();
			return nullptr;
		}

		static const char* GLShaderStageVKCachedFileExt(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return ".cached_vulkan.vert";
			case GL_FRAGMENT_SHADER: return ".cached_vulkan.frag";
			}

			unreachable();
			return nullptr;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_Filepath(filepath)
	{
		Utils::CreateCacheDirectoryIfAbsent();

		bool readSucces;
		std::string source = FileSystem::ReadFile(filepath, readSucces);

		if (!readSucces)
		{
			CL_CORE_ERROR("Failed to read shader file '{0}'!", filepath);
			return;
		}

		PreProcess(source);
		{
			Timer timer;

			CompileOrGetVulkanBinaries();
			CompileOrGetOpenGLBinaries();
			CreateProgram();

			// Immediately capture duration, calling ElapsedMs() while logging may and will delay the call to ElapsedMs().
			float elapsed = timer.ElapsedMs();
			CL_CORE_WARN("Shader creation took {0} ms.", elapsed);
		}

		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash != std::string::npos ? lastSlash + 1 : 0;
		size_t lastDot = filepath.rfind('.');
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		m_Sources[GL_VERTEX_SHADER] = vertexSrc;
		m_Sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		CompileOrGetVulkanBinaries();
		CompileOrGetOpenGLBinaries();
		CreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::PreProcess(const std::string& source)
	{
		const char* typeSpecifierToken = "#type";
		size_t tsTokenLength = strlen(typeSpecifierToken);
		size_t tsPos = source.find(typeSpecifierToken);

		while (tsPos != std::string::npos)
		{
			size_t lineEnd = source.find_first_of("\r\n", tsPos);
			verifyf(lineEnd != std::string::npos, "Shader syntax error!");

			size_t begin = tsPos + tsTokenLength + 1;
			std::string type = source.substr(begin, lineEnd - begin);

			verifyf(
				Utils::ShaderTypeFromString(type),
				"Invalid shader type specified! Use either 'vertex' for vertex shader code and 'fragment' or 'pixel' for fragment shader code."
			);

			size_t nextLinePos = source.find_first_not_of("\r\n", lineEnd);
			verifyf(nextLinePos != std::string::npos, "Syntax error!");

			tsPos = source.find(typeSpecifierToken, nextLinePos);
			m_Sources[Utils::ShaderTypeFromString(type)] = tsPos == std::string::npos ? source.substr(nextLinePos) : source.substr(nextLinePos, tsPos - nextLinePos);
		}
	}

	void OpenGLShader::CompileOrGetVulkanBinaries()
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
		options.SetOptimizationLevel(shaderc_optimization_level_performance);

		FileSystem::Path cacheDir = Utils::GetCacheDirectory();

		auto& shaderData = m_VulkanSPIRV;
		shaderData.clear();

		for (auto&& [stage, source] : m_Sources)
		{
			FileSystem::Path shaderFilepath = m_Filepath;
			FileSystem::Path cachedPath = cacheDir / (shaderFilepath.filename().string() + Utils::GLShaderStageVKCachedFileExt(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				std::streamsize size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*) data.data(), size);
			}
			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_Filepath.c_str(), options);

				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					CL_CORE_ERROR("Shader compilation failed! Output log: {0}", module.GetErrorMessage());
					check(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());
				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*) data.data(), data.size() * sizeof(uint32_t));
					out.flush();
				}
			}
		}

		for (auto&& [stage, data] : shaderData)
			Reflect(stage, data);
	}

	void OpenGLShader::CompileOrGetOpenGLBinaries()
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

		FileSystem::Path cacheDir = Utils::GetCacheDirectory();

		auto& shaderData = m_OpenGLSPIRV;
		shaderData.clear();
		m_Sources.clear();

		for (auto&& [stage, spirv] : m_VulkanSPIRV)
		{
			FileSystem::Path shaderFilepath = m_Filepath;
			FileSystem::Path cachedPath = cacheDir / (shaderFilepath.filename().string() + Utils::GLShaderStageGLCachedFileExt(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				std::streamsize size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*) data.data(), size);
			}
			else
			{
				spirv_cross::CompilerGLSL glslCompiler(spirv);
				m_Sources[stage] = glslCompiler.compile();
				auto& source = m_Sources[stage];

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_Filepath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					CL_CORE_ERROR("Shader compilation failed! Output log: {0}", module.GetCompilationStatus());
					check(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());
				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*) data.data(), data.size() * sizeof(uint32_t));
					out.flush();
				}
			}
		}
	}

	void OpenGLShader::Reflect(uint32_t stage, const std::vector<uint32_t>& data)
	{
		spirv_cross::Compiler compiler(data);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		CL_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", Utils::GLShaderStageToString(stage), m_Filepath);
		CL_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		CL_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		CL_CORE_TRACE("Uniform buffers:");
		for (const spirv_cross::Resource& resource : resources.uniform_buffers)
		{
			const spirv_cross::SPIRType& bufferType = compiler.get_type(resource.base_type_id);
			size_t bufferSz = compiler.get_declared_struct_size(bufferType);
			size_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			size_t memberCount = bufferType.member_types.size();

			CL_CORE_TRACE("  {0}", resource.name);
			CL_CORE_TRACE("    Size = {0}", bufferSz);
			CL_CORE_TRACE("    Binding = {0}", binding);
			CL_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	void OpenGLShader::CreateProgram()
	{
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_OpenGLSPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), (GLsizei)(spirv.size() * sizeof(uint32_t)));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);
		GLint result;

		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result != GL_TRUE)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::string infoLog(length, '\0');
			char* buffer = infoLog.data();

			glGetProgramInfoLog(program, length, &length, buffer);
			CL_CORE_ERROR("Shader linkage failed! Output log: {0}", infoLog);

			glDeleteProgram(program);
			for (GLuint id : shaderIDs)
				glDeleteShader(id);

			return;
		}

		for (GLuint id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererID = program;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name) const
	{
		return glGetUniformLocation(m_RendererID, name.c_str());
	}
}
