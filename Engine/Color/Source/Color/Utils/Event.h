#pragma once

#include "Core/Base.h"

#include <functional>
#include <vector>

namespace Color
{
	#define DECLARE_EVENT_TYPE(name, ...) typedef ::Color::Event<__VA_ARGS__> name
	#define BIND_METHOD(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

	template <typename... Params>
	class Event
	{
	public:
		using Binding = std::function<void(Params...)>;
	public:
		Event() = default;
		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		Event(std::initializer_list<Binding> bindings)
			: m_Bindings(bindings) { }

		void Bind(const Binding& binding)
		{
			m_Bindings.push_back(binding);
		}

		void Broadcast(Params... params) const
		{
			for (const Binding& binding : m_Bindings)
				binding(params...);
		}

		const std::vector<Binding>& GetBindings() const { return m_Bindings; }
	private:
		std::vector<Binding> m_Bindings;
	};
}
