#pragma once

#include <imgui/imgui.h>

#include "powernap/powernap.hpp"

namespace mapv
{
	class GUI_SearchSpeed
	{
	public:
		static void update(int& currentSpeed, pn::powernap& sleep, int& targetFramerate)
		{
			ImGui::SeparatorText("Search Speed");

			const char* currentSetting = (currentSpeed == 0 ? "Instant" : "Framerate");
			if (ImGui::Button("Select Speed Type"))
				ImGui::OpenPopup("speed-popup");

			ImGui::SetItemTooltip(
			"Instant: The search will run before the results are rendered to the screen.\n"
			"Framerate: The search will be visualised at the speed of the app's framerate, which can be adjusted with the Visualiser Speed slider.");

			ImGui::SameLine();
			ImGui::TextUnformatted(currentSetting);

			if (ImGui::BeginPopup("speed-popup"))
			{
				if (ImGui::Selectable("Instant"))
					currentSpeed = 0;

				if (ImGui::Selectable("Framerate"))
					currentSpeed = 1;

				ImGui::EndPopup();
			}

			if (currentSpeed == 1)
			{
				if (ImGui::SliderInt("Visualiser Speed", &targetFramerate, 16, 512)
					&& ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip))
				{
					sleep = pn::powernap{ targetFramerate };
				}
				ImGui::SetItemTooltip("NOTE: Visualiser speed is linked to framerate. Increasing speed may increase CPU/GPU load");
			}

			ImGui::NewLine();
		}
	};
}