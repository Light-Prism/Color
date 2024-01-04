#pragma once

#include "Renderer/RendererAPI.h"

namespace Color
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_API->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_API->SetViewport(x, y, width, height);
		}

		static void Clear()
		{
			s_API->Clear();
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_API->SetClearColor(color);
		}

		static void SetLineWidth(float width)
		{
			s_API->SetLineWidth(width);
		}
	private:
		static Scope<RendererAPI> s_API;
	};
}
