#include "ColorPCH.h"
#include "Buffer.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Color
{
	Ref<VertexBuffer> VertexBuffer::New(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLVertexBuffer>(size);
		}

		unreachable();
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::New(const float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLVertexBuffer>(vertices, size);
		}

		unreachable();
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::New(const uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::None: checkf(false, "RendererAPI::None isn't a valid API! Choose a valid one and try again."); return nullptr;
		case RendererAPI::OpenGL: return MakeScope<OpenGLIndexBuffer>(indices, count);
		}

		unreachable();
		return nullptr;
	}
}
