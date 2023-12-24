#include "EditorApp.h"

// >>> Entry Point Included Here <<<
// >>> Include in only one translation unit to avoid duplicate symbol names.
#include "Core/EntryPoint.h"

namespace Color
{
	EditorApp::EditorApp(const Color::CommandLineArgs& args)
		: Color::Application(args)
	{
	}

	EditorApp::~EditorApp()
	{
	}
}

IMPLEMENT_APPLICATION(Color::EditorApp);
IMPLEMENT_SPECIFICATION("Colorful", ".");
