#pragma once

#include "Core/Base.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include <glm/glm.hpp>

namespace Color
{
	class Input
	{
	public:
		virtual ~Input() = default;
	public:
		static bool IsKeyDown(KeyCode keycode)
		{
			return s_Instance->IsKeyDown_Impl(keycode);
		}

		static bool IsMouseButtonDown(MouseCode button)
		{
			return s_Instance->IsMouseButtonDown_Impl(button);
		}

		static glm::vec2 GetMousePosition()
		{
			return s_Instance->GetMousePosition_Impl();
		}

		static float GetMouseX()
		{
			return s_Instance->GetMouseX_Impl();
		}

		static float GetMouseY()
		{
			return s_Instance->GetMouseY_Impl();
		}
	protected:
		virtual bool IsKeyDown_Impl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonDown_Impl(MouseCode button) = 0;
		virtual glm::vec2 GetMousePosition_Impl() = 0;
		virtual float GetMouseX_Impl() = 0;
		virtual float GetMouseY_Impl() = 0;
	private:
		static Scope<Input> s_Instance;
	};
}
