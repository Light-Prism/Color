#pragma once

#include "Renderer/Shader.h"

namespace Color
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }
		virtual const std::string& GetFilepath() const override { return m_Filepath; }
	private:
		void PreProcess(const std::string& source);

		void CompileOrGetVulkanBinaries();
		void CompileOrGetOpenGLBinaries();
		void Reflect(uint32_t stage, const std::vector<uint32_t>& data);

		void CreateProgram();
		int GetUniformLocation(const std::string& name) const;
	private:
		uint32_t m_RendererID = 0;
		std::string m_Name, m_Filepath;

		std::unordered_map<uint32_t, std::vector<uint32_t>> m_OpenGLSPIRV;
		std::unordered_map<uint32_t, std::vector<uint32_t>> m_VulkanSPIRV;

		std::unordered_map<uint32_t, std::string> m_Sources;
	};
}
