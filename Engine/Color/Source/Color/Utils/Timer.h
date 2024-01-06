#pragma once

#include <chrono>

namespace Color
{
	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float Elapsed() const
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

		float ElapsedMs() const
		{
			return Elapsed() * 1000.0f;
		}

		float ElapsedSc() const
		{
			return ElapsedMs() * 1000.0f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}
