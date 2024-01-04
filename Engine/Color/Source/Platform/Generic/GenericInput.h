#pragma once

#include "Input/Input.h"

namespace Color
{
	class GenericInput : public Input
	{
	public:
		virtual ~GenericInput() = default;
	protected:
		virtual bool IsKeyDown_Impl(KeyCode keycode) override;
		virtual bool IsMouseButtonDown_Impl(MouseCode button) override;
		virtual glm::vec2 GetMousePosition_Impl() override;
		virtual float GetMouseX_Impl() override;
		virtual float GetMouseY_Impl() override;
	};
}
