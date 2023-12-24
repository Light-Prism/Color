#pragma once

#include "Core/Application.h"

namespace Color
{
	class EditorApp : public Color::Application
	{
	public:
		EditorApp(const Color::CommandLineArgs& args);
		virtual ~EditorApp() override;
	};
}
