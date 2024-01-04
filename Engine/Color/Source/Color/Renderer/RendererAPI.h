#pragma once

#include "Core/Base.h"

#include <glm/glm.hpp>

namespace Color
{
	class RendererAPI
	{
	public:
		enum API { None = 0, OpenGL = 1 };
		static const char* APIToString(API api);
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetLineWidth(float width) = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> New();
	private:
		inline static API s_API = OpenGL;
	};
}