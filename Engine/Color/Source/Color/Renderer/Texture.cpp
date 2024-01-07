#include "ColorPCH.h"
#include "Texture.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Color
{
	Ref<Texture2D> Texture2D::New(const TextureSpecification& specification)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLTexture2D>(specification);
		}

		unreachable();
		return nullptr;
	}

	Ref<Texture2D> Texture2D::New(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLTexture2D>(filepath);
		}

		unreachable();
		return nullptr;
	}
}
