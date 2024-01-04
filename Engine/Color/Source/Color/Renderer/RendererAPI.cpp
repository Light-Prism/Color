#include "ColorPCH.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Color
{
	const char* RendererAPI::APIToString(API api)
	{
		switch (api)
		{
		case None: return "None";
		case OpenGL: return "OpenGL";
		}

		unreachable();
		return nullptr;
	}

	Scope<RendererAPI> RendererAPI::New()
	{
		switch (s_API)
		{
		case None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case OpenGL: return MakeScope<OpenGLRendererAPI>();
		}

		unreachable();
		return nullptr;
	}
}
