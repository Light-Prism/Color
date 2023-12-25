#include "ColorPCH.h"
#include "ExitCode.h"

#include "Core/Application.h"

namespace Color
{
	void Exit(ExitCode::Type exitcode)
	{
		Application::Get()->Exit(exitcode);
	}
}
