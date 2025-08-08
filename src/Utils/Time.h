#pragma once

#include <chrono>

namespace mapv
{
	using HighResClock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::high_resolution_clock::time_point;

	class Time
	{
	public:
		static const float deltaTime();
		void updateTimestep();

	private:
		inline static float s_deltaTime = 0.f;

		TimePoint m_previous;
		TimePoint m_current;
		std::chrono::duration<float> m_timestep;
	};

	class Duration
	{
		friend class Clock;

	public:
		std::uint64_t seconds();
		float secondsf();
		std::uint64_t milliseconds();
		float millisecondsf();
		std::uint64_t microseconds();
		float microsecondsf();

	private:
		HighResClock m_clock;
		TimePoint m_start;
		TimePoint m_end;

	private:
		Duration(HighResClock clock, TimePoint start);
	};

	class Clock
	{
	public:
		Duration getTime();

		Clock();

	private:
		HighResClock m_clock;
		TimePoint m_start;
	};
}