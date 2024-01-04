#pragma once

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Color
{
	class GenericWindow : public Window
	{
	public:
		GenericWindow(const WindowProps& props);
		virtual ~GenericWindow() override;

		virtual bool Init() override;
		virtual bool IsOpen() const override;
		virtual void Update() override;
		virtual bool Destroy() override;

		virtual void SetTitle(const std::string& title) override;
		virtual void SetSize(uint32_t width, uint32_t height) override;
		virtual void SetWidth(uint32_t width) override;
		virtual void SetHeight(uint32_t height) override;
		virtual void SetVSync(bool vSync) override;

		virtual const std::string& GetTitle() const override { return m_Data.Title; }
		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }
		virtual bool IsResizable() const override { return m_Data.Resizable; }
		virtual bool IsFullscreen() const override { return m_Data.Fullscreen; }
		virtual bool IsVSync() const override { return m_Data.VSync; }
		virtual void* GetNativeWindowHandle() const override { return m_Handle; }
	private:
		Scope<GraphicsContext> m_Context;
		GLFWwindow* m_Handle = nullptr;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool Resizable, Fullscreen, VSync;

			OnWindowClosed& OnClose;
			OnWindowResized& OnResize;
			OnKeyPressed& OnKeyPress;
			OnKeyReleased& OnKeyRelease;
			OnKeyTyped& OnKeyType;
			OnMouseButtonPressed& OnMouseButtonPress;
			OnMouseButtonReleased& OnMouseButtonRelease;
			OnMouseScrolled& OnMouseScroll;
			OnMouseMoved& OnMouseMove;
		} m_Data;
	};
}
