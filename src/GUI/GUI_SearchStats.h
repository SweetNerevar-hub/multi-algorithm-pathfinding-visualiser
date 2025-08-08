#pragma once

#include <imgui/imgui.h>

#include "../SearchAlgorithms/AlgorithmBase.h"

namespace mapv
{
	class GUI_SearchStats
	{
	public:
		static void update(AlgorithmBase& algo)
		{
			ImGui::NewLine();
			ImGui::Text("Search Time: %.2f %s", algo.searchTime(), "ms");
			ImGui::Text("Nodes Searched: %d", algo.nodesSearched());
			ImGui::Text("Path Length: %d", algo.pathLength());
		}
	};
}