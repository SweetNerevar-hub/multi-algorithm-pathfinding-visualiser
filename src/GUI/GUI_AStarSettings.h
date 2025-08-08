#pragma once

#include "../SearchAlgorithms/AStar.h"

namespace mapv
{
	class GUI_AStarSettings
	{
	public:
		static void update(std::unique_ptr<AlgorithmBase>& algo)
		{
			AStar* as = static_cast<AStar*>(algo.get());
			const char* heuristics[] = { "Euclidian", "Octile", "Chebyshev" };

			ImGui::SliderFloat("Weight", &as->weight, 0.f, 2.f, "%.1f");
			ImGui::SetItemTooltip("The 'Weight' influences how much the heuristic affects the greediness/aggressiveness of the search.\n"
								  "A lower value will result in a broader search (a weight of 0 is equivalent to Dijkstra's algorithm).\n"
								  "A higher value will result in a greedier search.\n\n"
								  "NOTE: Although a greedier search may produce faster searches, it may also produce less optimal paths");

			if (ImGui::Button("Select Heuristic"))
				ImGui::OpenPopup("heuristic_popup");
			ImGui::SameLine();
			ImGui::TextUnformatted(heuristics[(int)as->h]);
			if (ImGui::BeginPopup("heuristic_popup"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(heuristics); i++)
				{
					if (ImGui::Selectable(heuristics[i]))
					{
						as->h = ((AStar::Heuristic)i);
					}
				}

				ImGui::EndPopup();
			}

			ImGui::NewLine();
		}
	};
}