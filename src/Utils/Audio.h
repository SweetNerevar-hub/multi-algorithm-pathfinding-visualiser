#pragma once

#include <vector>
#include <iostream>

#include "miniaudio/miniaudio.h"

namespace mapv
{
	class Audio
	{
	public:
		enum Sound
		{
			PATHFINDING_COMPLETE,
			UI_HOVER,
			UI_SELECT
		};

		static Audio& get()
		{
			static Audio instance;
			return instance;
		}

		void setAudioActive(bool doPlay);
		void loadSound(const char* path);
		void playSound(Sound soundType);

		Audio(Audio const&) = delete;
		void operator=(Audio const&) = delete;

	private:
		ma_engine* m_engine = new ma_engine();
		std::vector<ma_sound> m_sounds;
		bool m_isEnabled = true;

	private:
		Audio();
		~Audio();
	};
}