#pragma once

#include "Renderer/Texture.h"

namespace Color
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureSpecification& specification);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void SetData(const void* data, uint32_t size) override;

		virtual const std::string& GetFilepath() const override { return m_Filepath; }
		virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual bool IsLoaded() const override { return m_IsLoaded; }
		virtual bool operator==(const Texture& other) const override { return m_RendererID == other.GetRendererID(); }
	private:
		uint32_t m_RendererID = 0;

		TextureSpecification m_Specification;
		std::string m_Filepath;

		uint32_t m_Width = 0, m_Height = 0;
		bool m_IsLoaded = false;

		uint32_t m_InternalFormat = 0, m_DataFormat = 0;
	};
}
