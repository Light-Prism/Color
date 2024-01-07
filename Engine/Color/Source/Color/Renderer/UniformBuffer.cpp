#include "ColorPCH.h"
#include "UniformBuffer.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Color
{
	Ref<UniformBuffer> UniformBuffer::New(uint32_t size, uint32_t binding)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLUniformBuffer>(size, binding);
		}

		unreachable();
		return nullptr;
	}
}
