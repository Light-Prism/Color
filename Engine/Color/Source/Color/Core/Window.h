#pragma once

#include "Core/Base.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include "Utils/Event.h"

namespace Color
{
	DECLARE_EVENT_TYPE(OnWindowClosed);
	DECLARE_EVENT_TYPE(OnWindowResized, uint32_t /*width*/, uint32_t /*height*/);
	DECLARE_EVENT_TYPE(OnKeyPressed, KeyCode /*keycode*/, bool /*isRepeat*/);
	DECLARE_EVENT_TYPE(OnKeyReleased, KeyCode /*keycode*/);
	DECLARE_EVENT_TYPE(OnKeyTyped, KeyCode /*keycode*/);
	DECLARE_EVENT_TYPE(OnMouseButtonPressed, MouseCode /*button*/);
	DECLARE_EVENT_TYPE(OnMouseButtonReleased, MouseCode /*button*/);
	DECLARE_EVENT_TYPE(OnMouseScrolled, float /*xOffset*/, float /*yOffset*/);
	DECLARE_EVENT_TYPE(OnMouseMoved, float /*xPos*/, float /*yPos*/);

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;
		bool Resizable, Fullscreen, VSync;

		WindowProps(const std::string& title = "Color Window",
					uint32_t width = 1600,
					uint32_t height = 900,
					bool resizable = false,
					bool fullscreen = false,
					bool vSync = true)
			: Title(title), Width(width), Height(height), Resizable(resizable), Fullscreen(fullscreen), VSync(vSync)
		{
		}
	};

	class Window
	{
	public:
		OnWindowClosed OnClose;
		OnWindowResized OnResize;
		OnKeyPressed OnKeyPress;
		OnKeyReleased OnKeyRelease;
		OnKeyTyped OnKeyType;
		OnMouseButtonPressed OnMouseButtonPress;
		OnMouseButtonReleased OnMouseButtonRelease;
		OnMouseScrolled OnMouseScroll;
		OnMouseMoved OnMouseMove;
	public:
		virtual ~Window() = default;

		virtual bool Init() = 0;
		virtual bool IsOpen() const = 0;
		virtual void Update() = 0;
		virtual bool Destroy() = 0;

		virtual void SetTitle(const std::string& title) = 0;
		virtual void SetSize(uint32_t width, uint32_t height) = 0;
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;
		virtual void SetVSync(bool vSync) = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual bool IsResizable() const = 0;
		virtual bool IsFullscreen() const = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindowHandle() const = 0;

		static Scope<Window> New(const WindowProps& props = {});
	};
}
