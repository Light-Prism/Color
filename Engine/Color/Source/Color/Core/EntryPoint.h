#pragma once

#include "Core/Application.h"

namespace Color
{
	int EngineMain(int argc, char** argv)
	{
		Application* application = CreateApplication({ argv, (uint32_t) argc });
		application->Run();

		delete application;
		return 0;
	}
}

#if defined CL_SHIPPING && defined CL_PLATFORM_WINDOWS

#include <Windows.h>

int CALLBACK WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
)
{
	return Color::EngineMain(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Color::EngineMain(argc, argv);
}

#endif
