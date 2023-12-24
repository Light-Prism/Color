#pragma once

#include "Core/Application.h"

namespace Sandbox
{
	class SandboxApp : public Color::Application
	{
	public:
		SandboxApp(const Color::CommandLineArgs& args);
		virtual ~SandboxApp() override;
	};
}
