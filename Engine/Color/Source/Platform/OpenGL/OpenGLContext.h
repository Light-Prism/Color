#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Color
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual ~OpenGLContext() = default;

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};
}
