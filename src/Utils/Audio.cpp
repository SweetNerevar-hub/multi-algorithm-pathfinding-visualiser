#include "Audio.h"

namespace mapv
{
	Audio::Audio()
	{
		ma_result result = ma_engine_init(nullptr, m_engine);
		if (result != MA_SUCCESS)
		{
			std::cout << "Couldn't init engine!" << std::endl;
			std::cout << "Error code: " << result << std::endl;
			return;
		}
		
		ma_engine_start(m_engine);
		m_sounds.reserve(3);
	}

	Audio::~Audio()
	{
		ma_engine_uninit(m_engine);
		for (ma_sound& sound : m_sounds)
		{
			ma_sound_uninit(&sound);
		}
	}

	void Audio::setAudioActive(bool doPlay)
	{
		m_isEnabled = doPlay;
	}

	void Audio::loadSound(const char* path)
	{
		m_sounds.emplace_back(ma_sound());
		ma_result result = ma_sound_init_from_file(m_engine, path, MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, &m_sounds.back());

		if (result != MA_SUCCESS)
		{
			std::cout << "Couldn't load sound from file!" << std::endl;
			std::cout << "Error code: " << result << std::endl;
			m_sounds.pop_back();
			return;
		}
	}

	void Audio::playSound(Sound soundType)
	{
		if (m_isEnabled)
			ma_sound_start(&m_sounds[(int)soundType]);
	}
}