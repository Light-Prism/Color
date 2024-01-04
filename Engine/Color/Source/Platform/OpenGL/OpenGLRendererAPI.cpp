#include "ColorPCH.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Color
{
	static void	OpenGLMessageCallback
	(
		unsigned src,
		unsigned type,
		unsigned id,
		unsigned severity,
		int len,
		const char* msg,
		const void* usrex
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         CL_CORE_FATAL(msg); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       CL_CORE_ERROR(msg); return;
		case GL_DEBUG_SEVERITY_LOW:          CL_CORE_WARN(msg); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: CL_CORE_TRACE(msg); return;
		}

		unreachable();
	}

	void OpenGLRendererAPI::Init()
	{
	#ifndef CL_SHIPPING
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}
}
