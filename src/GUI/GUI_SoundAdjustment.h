#pragma once

#include <imgui/imgui.h>

#include "../Utils/Audio.h"

namespace mapv
{
	class GUI_SoundAdjustment
	{
	public:
		static void update()
		{
			ImGui::SeparatorText("Audio Settings");

			if (ImGui::Checkbox("Toggle Audio", &m_audioEnabled))
				Audio::get().setAudioActive(m_audioEnabled);

			ImGui::NewLine();
		}

	private:
		inline static bool m_audioEnabled = true;
	};
}