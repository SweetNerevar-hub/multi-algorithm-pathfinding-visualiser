#pragma once

#include <typeindex>

#include "../SearchAlgorithms/BFS.h"
#include "../SearchAlgorithms/AStar.h"

namespace mapv
{
	class GUI_SelectSearchAlgorithm
	{
	public:
		GUI_SelectSearchAlgorithm() = default;

		static void update(std::unique_ptr<AlgorithmBase>& algo, VertexArray& tilesVA)
		{
			std::string algos[] = { "DFS", "BFS", "Dijkstra", "A*" };

			ImGui::SeparatorText("Search Algorithm");

			if (ImGui::Button("Select Algorithm"))
				ImGui::OpenPopup("algo_popup");
			ImGui::SameLine();
			ImGui::TextUnformatted(algos[s_selectedAlgoIndex].c_str());
			if (ImGui::BeginPopup("algo_popup"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(algos); i++)
				{
					if (ImGui::Selectable(algos[i].c_str()))
					{
						setAlgorithm(algo, tilesVA, i);
					}
				}

				ImGui::EndPopup();
			}
		}

	private:
		inline static int s_selectedAlgoIndex = 0;

	private:
		static void setAlgorithm(std::unique_ptr<AlgorithmBase>& algo, VertexArray& tilesVA, int i)
		{
			if (i == s_selectedAlgoIndex)
				return;

			s_selectedAlgoIndex = i;
			switch (i)
			{
			case 0:
				algo = std::make_unique<DFS>(tilesVA);
				break;

			case 1:
				algo = std::make_unique<BFS>(tilesVA);
				break;

			case 2:
				algo = std::make_unique<Dijkstra>(tilesVA);
				break;

			case 3:
				algo = std::make_unique<AStar>(tilesVA);
				break;
			}
		}
	};
}