#include "ColorPCH.h"
#include "OpenGLTexture.h"

#include "Utils/Timer.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Color
{
	static GLenum ColorImageFormatToGLDataFormat(ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::RGB8:  return GL_RGB;
		case ImageFormat::RGBA8: return GL_RGBA;
		}

		unreachable();
		return 0;
	}

	static GLenum ColorImageFormatToGLInternalFormat(ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::RGB8:  return GL_RGB8;
		case ImageFormat::RGBA8: return GL_RGBA8;
		}

		unreachable();
		return 0;
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification)
		: m_Specification(specification), m_Width(specification.Width), m_Height(specification.Height),
		  m_InternalFormat(ColorImageFormatToGLInternalFormat(specification.Format)),
		  m_DataFormat(ColorImageFormatToGLDataFormat(specification.Format))
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_Filepath(filepath)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		stbi_uc* data = nullptr;
		{
			Timer timer;
			data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

			float elapsed = timer.ElapsedMs();
			CL_CORE_WARN("Loading image '{0}' (via stbi_load) took {1} ms.", filepath, elapsed);
		}

		if (data)
		{
			m_IsLoaded = true;

			m_Width = width;
			m_Height = height;

			if (channels == 4)
			{
				m_InternalFormat = GL_RGBA8;
				m_DataFormat     = GL_RGBA;
			}
			else if (channels == 3)
			{
				m_InternalFormat = GL_RGB8;
				m_DataFormat     = GL_RGB;
			}
			else
			{
				CL_CORE_FATAL("Color only supports 3 or 4 channel images!");
			}

			verifyf(m_InternalFormat & m_DataFormat, "Unsupported image format!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetData(const void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		verifyf(size == m_Width * m_Height * bpp, "Data must contain/fill the entirety of the texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
}
