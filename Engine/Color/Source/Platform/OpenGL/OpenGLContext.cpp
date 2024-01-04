#include "ColorPCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Color
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		checkf(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			CL_CORE_FATAL("Failed to initialize Glad!");

		CL_CORE_INFO("OpenGL Info:");
		CL_CORE_INFO("  Vendor   -> {0}", (const char*) glGetString(GL_VENDOR));
		CL_CORE_INFO("  Renderer -> {0}", (const char*) glGetString(GL_RENDERER));
		CL_CORE_INFO("  Version  -> {0}", (const char*) glGetString(GL_VERSION));
		CL_CORE_INFO("  GLSL     -> {0}", (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5))
			CL_CORE_FATAL("A graphics card with at least OpenGL version 4.5 support is required!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}