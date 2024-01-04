#include "ColorPCH.h"
#include "GenericInput.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Color
{
	bool GenericInput::IsKeyDown_Impl(KeyCode keycode)
	{
		GLFWwindow* window = (GLFWwindow*) Application::Get()->GetWindow().GetNativeWindowHandle();
		int status = glfwGetKey(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	bool GenericInput::IsMouseButtonDown_Impl(MouseCode button)
	{
		GLFWwindow* window = (GLFWwindow*) Application::Get()->GetWindow().GetNativeWindowHandle();
		int status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}

	glm::vec2 GenericInput::GetMousePosition_Impl()
	{
		GLFWwindow* window = (GLFWwindow*)Application::Get()->GetWindow().GetNativeWindowHandle();
		double x, y;

		glfwGetCursorPos(window, &x, &y);
		return { (float) x, (float) y };
	}

	float GenericInput::GetMouseX_Impl()
	{
		return GetMousePosition_Impl().x;
	}

	float GenericInput::GetMouseY_Impl()
	{
		return GetMousePosition_Impl().y;
	}
}
