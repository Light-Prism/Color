#pragma once

#include "Renderer/RendererAPI.h"

namespace Color
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
