#include "ColorPCH.h"
#include "Input.h"

#include "Platform/Windows/WindowsInput.h"
#include "Platform/Linux/LinuxInput.h"

namespace Color
{
	Scope<Input> Input::s_Instance = MakeScope<ConcatWithPlatformName(Input)>();
}
