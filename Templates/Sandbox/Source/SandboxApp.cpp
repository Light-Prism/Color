#include "SandboxApp.h"

// >>> Entry Point Included Here <<<
// >>> Include in only one translation unit to avoid duplicate symbol names.
#include "Core/EntryPoint.h"

#include "Renderer/Buffer.h"

namespace Sandbox
{
	Color::Ref<Color::VertexBuffer> VBO;
	Color::Ref<Color::IndexBuffer>  IBO;

	SandboxApp::SandboxApp(const Color::CommandLineArgs& args)
		: Color::Application(args)
	{
		// Temporary testing

		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		VBO = Color::VertexBuffer::New(vertices, sizeof(vertices));
		VBO->SetLayout({
			{ Color::ShaderDataType::Float3, "a_Position" }
		});

		IBO = Color::IndexBuffer::New(indices, 6);
		IBO->Bind();
	}

	SandboxApp::~SandboxApp()
	{
	}
}

IMPLEMENT_APPLICATION(Sandbox::SandboxApp);
IMPLEMENT_SPECIFICATION("Sandbox", ".");
