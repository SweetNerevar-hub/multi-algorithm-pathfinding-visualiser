#pragma once

#ifdef _WIN32
	#include <windows.h>

	#define BEGIN_TIME_PERIOD	{ timeBeginPeriod(1); }
	#define END_TIME_PERIOD		{ timeEndPeriod(1); }
#endif
#ifndef _WIN32
	#define BEGIN_TIME_PERIOD	{ }
	#define END_TIME_PERIOD		{ }
#endif

#include <chrono>
#include <thread>

namespace pn
{
	class powernap
	{
		using time_point_double = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<double, std::nano>>;

	public:
		/*
		\brief Ctor

		\param targetFramerate:	This determines how long the thread will sleep for
								by getting the frametime (1 / targetFramerate) 
								in milliseconds and using that time to calculate the amount of sleep required
		*/
		powernap(std::int64_t targetFramerate) :
			m_frameTimeLength(std::chrono::duration<double>(1.0 / targetFramerate))
		{
			BEGIN_TIME_PERIOD
		}
		~powernap() { END_TIME_PERIOD }

		/*
		\brief	Place at the start of the app's loop.
				This will get the time at which the frame has started
		*/
		void frameStart()
		{
			m_frameStartTime = std::chrono::high_resolution_clock::now();
		}

		/*
		\brief	Place after all the loop's logic has concluded.
				Puts this thread to sleep based on how much time is remaining during the desired frametime
		*/
		void sleep()
		{
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			time_point_double nextFrameTime = m_frameStartTime + m_frameTimeLength;

			/* The extra millisecond gives some leeway when the CPU wakes this thread so as not to be too late */
			std::chrono::microseconds sleepTime = std::chrono::duration_cast<std::chrono::microseconds>((nextFrameTime - now) - std::chrono::milliseconds(1));

			if (sleepTime.count() > 0.f)
				std::this_thread::sleep_for(sleepTime);

			spinWait(std::chrono::high_resolution_clock::now() < nextFrameTime);
		}

	private:
		std::chrono::duration<double> m_frameTimeLength;
		std::chrono::high_resolution_clock::time_point m_frameStartTime;

	private:
		void spinWait(bool condition)
		{
			std::chrono::high_resolution_clock::time_point spinStart = std::chrono::high_resolution_clock::now();
			std::chrono::microseconds minThreshold = std::chrono::microseconds(5);

			while (condition)
			{
				/* Prevents an infinite while loop due to a potential negative number occuring */
				if (std::chrono::high_resolution_clock::now() - spinStart > minThreshold)
					break;
			}
		}
	};
}