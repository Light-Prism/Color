#include "SandboxApp.h"

// >>> Entry Point Included Here <<<
// >>> Include in only one translation unit to avoid duplicate symbol names.
#include "Core/EntryPoint.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace Sandbox
{
	Color::Ref<Color::Shader> Shader;
	Color::Ref<Color::VertexArray> VAO;
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

		Shader = Color::Shader::New("Assets/Shaders/FlatColor.glsl");
		Shader->Bind();

		VAO = Color::VertexArray::New();
		VAO->Bind();

		VBO = Color::VertexBuffer::New(vertices, sizeof(vertices));
		VBO->SetLayout({
			{ Color::ShaderDataType::Float3, "a_Position" }
		});

		IBO = Color::IndexBuffer::New(indices, 6);
		IBO->Bind();

		VAO->AddVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);
	}

	SandboxApp::~SandboxApp()
	{
	}

	void SandboxApp::PreTick()
	{
		Color::RenderCommand::Clear();

		// This would only render if the vendor-specific OpenGL driver has a default shader (nonstandard) since we currently don't provide one ourselves.
		Color::RenderCommand::DrawIndexed(VAO);
	}

	void SandboxApp::PostTick()
	{
	}
}

IMPLEMENT_APPLICATION(Sandbox::SandboxApp);
IMPLEMENT_SPECIFICATION("Sandbox", "../../Engine/Colorful");
