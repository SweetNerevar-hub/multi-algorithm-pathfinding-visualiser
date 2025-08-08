#pragma once

#include <imgui/imgui.h>

namespace mapv
{
	class GUI_NodeCost
	{
	public:
		static void update()
		{
			if (ImGui::InputInt("Node Cost", &s_costValue, 10))
			{
				if (s_costValue < 0)
					s_costValue = 0;

				else if (s_costValue > 99)
					s_costValue = 99;
			}

			ImGui::NewLine();
		}

		static int getCostValue() { return s_costValue; }

	private:
		inline static int s_costValue = 0;
	};
}