#include "Time.h"

namespace mapv
{
	/* Time Methods */
	// ------------ //
	const float Time::deltaTime()
	{
		return s_deltaTime;
	}

	void Time::updateTimestep()
	{
		m_current = HighResClock::now();
		m_timestep = m_current - m_previous;
		m_previous = m_current;
		s_deltaTime = m_timestep.count();
	}

	/* Clock Methods */
	// ------------- //
	Clock::Clock()
	{
		m_start = m_clock.now();
	}

	Duration Clock::getTime()
	{
		Duration dur{ m_clock, m_start };
		return dur;
	}

	/* Duration Methods */
	// ---------------- //
	Duration::Duration(HighResClock clock, TimePoint start) :
		m_clock(clock),
		m_start(start) { }

	std::uint64_t Duration::seconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_end - m_start).count();
	}

	float Duration::secondsf()
	{
		TimePoint m_end = m_clock.now();
		return std::chrono::duration_cast<std::chrono::duration<float>>(m_end - m_start).count();
	}

	std::uint64_t Duration::milliseconds()
	{
		TimePoint m_end = m_clock.now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
	}

	float Duration::millisecondsf()
	{
		TimePoint m_end = m_clock.now();
		return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(m_end - m_start).count();
	}

	std::uint64_t Duration::microseconds()
	{
		TimePoint m_end = m_clock.now();
		return std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count();
	}

	float Duration::microsecondsf()
	{
		TimePoint m_end = m_clock.now();
		return std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(m_end - m_start).count();
	}
}