#include "ColorPCH.h"
#include "GraphicsContext.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Color
{
	Scope<GraphicsContext> GraphicsContext::New(void* windowHandle)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLContext>((GLFWwindow*) windowHandle);
		}

		unreachable();
		return nullptr;
	}
}
