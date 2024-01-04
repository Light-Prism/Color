#include "ColorPCH.h"
#include "GenericWindow.h"

#include "Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

namespace Color
{
	static uint8_t s_WindowCount = 0;

	static void GLFWErrorCallback(int errorcode, const char* message)
	{
		CL_CORE_ERROR("GLFW Error ({0}): {1}", errorcode, message);
	}

	GenericWindow::GenericWindow(const WindowProps& props)
		: m_Data
		  {
		      props.Title,
			  props.Width,
			  props.Height,
			  props.Resizable,
			  props.Fullscreen,
			  props.VSync,

			  OnClose,
			  OnResize,
			  OnKeyPress,
			  OnKeyRelease,
			  OnKeyType,
			  OnMouseButtonPress,
			  OnMouseButtonRelease,
			  OnMouseScroll,
			  OnMouseMove
		  }
	{
	}

	GenericWindow::~GenericWindow()
	{
		Destroy();
	}

	bool GenericWindow::Init()
	{
		CL_CORE_INFO("Creating window '{0}' ({1}x{2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (s_WindowCount == 0)
		{
			if (!glfwInit())
			{
				CL_CORE_ERROR("Failed to initialize GLFW!");
				return false;
			}

			glfwSetErrorCallback(GLFWErrorCallback);
		}

	#ifndef CL_SHIPPING
		if (RendererAPI::GetAPI() == RendererAPI::OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#endif

		glfwWindowHint(GLFW_RESIZABLE, m_Data.Resizable ? GLFW_TRUE : GLFW_FALSE);
		GLFWmonitor* monitor = m_Data.Fullscreen ? glfwGetPrimaryMonitor() : nullptr;

		m_Handle = glfwCreateWindow
		(
			m_Data.Width,
			m_Data.Height,
			m_Data.Title.c_str(),
			monitor,
			nullptr
		);

		if (!m_Handle)
		{
			CL_CORE_ERROR("Failed to create the GLFW window handle!");
			return false;
		}

		m_Context = GraphicsContext::New(m_Handle);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Handle, &m_Data);
		glfwSwapInterval(m_Data.VSync ? 1 : 0);

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.OnClose.Broadcast();
		});
		
		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			data.OnResize.Broadcast(width, height);
		});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int keycode, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				data.OnKeyPress.Broadcast(keycode, false);
				break;
			}
			case GLFW_REPEAT:
			{
				data.OnKeyPress.Broadcast(keycode, true);
				break;
			}
			case GLFW_RELEASE:
			{
				data.OnKeyRelease.Broadcast(keycode);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.OnKeyType.Broadcast(keycode);
		});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				data.OnMouseButtonPress.Broadcast(button);
				break;
			}
			case GLFW_RELEASE:
			{
				data.OnMouseButtonRelease.Broadcast(button);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.OnMouseScroll.Broadcast((float) xOffset, (float) yOffset);
		});
		
		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.OnMouseMove.Broadcast((float) xPos, (float) yPos);
		});

		s_WindowCount++;
		return true;
	}

	bool GenericWindow::IsOpen() const
	{
		return m_Handle && !glfwWindowShouldClose(m_Handle);
	}

	void GenericWindow::Update()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	bool GenericWindow::Destroy()
	{
		if (!IsOpen())
			return false;

		glfwDestroyWindow(m_Handle);
		m_Handle = nullptr;

		if (--s_WindowCount == 0)
		{
			glfwTerminate();
			CL_CORE_TRACE("The destroyed window was the last alive window, terminated GLFW as there are no windows left alive.");
		}

		return true;
	}

	void GenericWindow::SetTitle(const std::string& title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Handle, title.c_str());
	}

	void GenericWindow::SetSize(uint32_t width, uint32_t height)
	{
		glfwSetWindowSize(m_Handle, width, height);
	}

	void GenericWindow::SetWidth(uint32_t width)
	{
		SetSize(width, m_Data.Height);
	}

	void GenericWindow::SetHeight(uint32_t height)
	{
		SetSize(m_Data.Width, height);
	}

	void GenericWindow::SetVSync(bool vSync)
	{
		m_Data.VSync = vSync;
		glfwSwapInterval(vSync ? 1 : 0);
	}
}
