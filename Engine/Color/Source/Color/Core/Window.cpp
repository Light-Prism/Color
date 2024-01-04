#include "ColorPCH.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Linux/LinuxWindow.h"

namespace Color
{
	Scope<Window> Window::New(const WindowProps& props)
	{
		return MakeScope<ConcatWithPlatformName(Window)>(props);
	}
}
