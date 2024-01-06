#include "ColorPCH.h"
#include "Shader.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Color
{
	Ref<Shader> Shader::New(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLShader>(filepath);
		}

		unreachable();
		return nullptr;
	}

	Ref<Shader> Shader::New(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		unreachable();
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		checkf(!Exists(name), "Shader already exists!");
		m_ShaderMap[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::New(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		checkf(!Exists(name), "Shader already exists!");
		Ref<Shader> shader = Shader::New(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		checkf(Exists(name), "Shader doesn't exist!");
		return m_ShaderMap[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_ShaderMap.contains(name);
	}
}
