#include "SandboxApp.h"

// >>> Entry Point Included Here <<<
// >>> Include in only one translation unit to avoid duplicate symbol names.
#include "Core/EntryPoint.h"

namespace Sandbox
{
	SandboxApp::SandboxApp(const Color::CommandLineArgs& args)
		: Color::Application(args)
	{
	}

	SandboxApp::~SandboxApp()
	{
	}
}

IMPLEMENT_APPLICATION(Sandbox::SandboxApp);
IMPLEMENT_SPECIFICATION("Sandbox", ".");
