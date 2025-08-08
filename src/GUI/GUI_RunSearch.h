#pragma once

#include <imgui/imgui.h>

#include "../Map.h"
#include "../SearchAlgorithms/AlgorithmBase.h"

namespace mapv
{
	class GUI_RunSearch
	{
	public:
		static void update(Map& map, AlgorithmBase& algo, int searchSpeed)
		{
			ImGui::NewLine();
			if (ImGui::Button("Run Search"))
			{
				map.findNeighbours();

				Tile* start = map.getStartTile();
				Tile* goal = map.getGoalTile();
				algo.init(start, goal);

				if (searchSpeed == 0)
					algo.instantSearch();
			}
		}
	};
}