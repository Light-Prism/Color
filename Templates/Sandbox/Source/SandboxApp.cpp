#include "SandboxApp.h"

// >>> Entry Point Included Here <<<
// >>> Include in only one translation unit to avoid duplicate symbol names.
#include "Core/EntryPoint.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

namespace Sandbox
{
	Color::Ref<Color::Texture2D> Texture;
	Color::Ref<Color::Shader> Shader;
	Color::Ref<Color::UniformBuffer> UBO;
	Color::Ref<Color::VertexArray> VAO;
	Color::Ref<Color::VertexBuffer> VBO;
	Color::Ref<Color::IndexBuffer>  IBO;

	SandboxApp::SandboxApp(const Color::CommandLineArgs& args)
		: Color::Application(args)
	{
		// Temporary testing

		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f
		};

		uint32_t indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		Texture = Color::Texture2D::New("Assets/Textures/Light_Prism_Logo_Banner.png");
		Texture->Bind();

		Shader = Color::Shader::New("Assets/Shaders/Textured.glsl");
		Shader->Bind();

		UBO = Color::UniformBuffer::New(sizeof(int), 0);
		UBO->SetData(0, sizeof(int));

		VAO = Color::VertexArray::New();
		VAO->Bind();

		VBO = Color::VertexBuffer::New(vertices, sizeof(vertices));
		VBO->SetLayout({
			{ Color::ShaderDataType::Float3, "a_Position" },
			{ Color::ShaderDataType::Float4, "a_Color" },
			{ Color::ShaderDataType::Float2, "a_TexCoord" }
		});

		IBO = Color::IndexBuffer::New(indices, 6);
		IBO->Bind();

		VAO->AddVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);

		//Color::RenderCommand::SetClearColor({ 1.0f, 1.0f, 0.0f, 1.0f });
	}

	SandboxApp::~SandboxApp()
	{
	}

	void SandboxApp::PreTick()
	{
		Color::RenderCommand::Clear();
		Color::RenderCommand::DrawIndexed(VAO);
	}

	void SandboxApp::PostTick()
	{
	}
}

IMPLEMENT_APPLICATION(Sandbox::SandboxApp);
IMPLEMENT_SPECIFICATION("Sandbox", "../../Engine/Colorful");
