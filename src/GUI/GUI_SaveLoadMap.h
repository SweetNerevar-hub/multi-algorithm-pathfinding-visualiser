#pragma once

#include <imgui/imgui.h>

#include "../Map.h"

namespace mapv
{
	class GUI_SaveLoadMap
	{
	public:
		static void update(Map& map)
		{
			ImGui::NewLine();
			ImGui::SeparatorText("Saving/Loading Maps");

			ImGui::InputText("Map Name", s_contents, IM_ARRAYSIZE(s_contents));
			if (ImGui::Button("Save Map"))
				map.saveMap(s_contents);

			else if (ImGui::Button("Load Map"))
				map.loadMap(s_contents);

			ImGui::NewLine();
		}

	private:
		inline static char s_contents[32];
	};
}