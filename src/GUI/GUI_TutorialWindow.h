#pragma once

namespace mapv
{
	class GUI_TutorialWindow
	{
	public:
		static void update()
		{
			const char* toggle = s_showTutorialWindow ? "Hide Tutorial" : "Show Tutorial";

			if (ImGui::Button(toggle))
				s_showTutorialWindow = !s_showTutorialWindow;

			toggleTutorialWindow();
			ImGui::NewLine();
		}

	private:
		inline static bool s_showTutorialWindow = true;

	private:
		static void toggleTutorialWindow()
		{
			if (s_showTutorialWindow)
			{
				if (ImGui::Begin("Tutorial", &s_showTutorialWindow))
				{
					controls();
					nodeCostPainting();
					savingLoadingMaps();
				}

				ImGui::End();
			}
		}

		static void controls()
		{
			ImGui::SeparatorText("Controls");
			ImGui::BulletText("Left Mouse Click: Set node to Closed");
			ImGui::BulletText("Right Mouse Click: Set node to Open");
			ImGui::BulletText("S + Left Mouse Click: Set Start node");
			ImGui::BulletText("G + Left Mouse Click: Set Goal node");
			ImGui::BulletText("ESC: Cancel search");
			ImGui::NewLine();
		}

		static void nodeCostPainting()
		{
			ImGui::SeparatorText("Node Cost Painting");
			ImGui::TextWrapped("You can think of node costs as adding extra effort for traversing one node to another. This affects how Dijkstra's and A* finds the shortest path, by turning it into more of a path of least resistance.");
			ImGui::NewLine();
			ImGui::TextWrapped("Adjusting the Node Cost value can be accessed by selecting either: Dijkstra's algorithm or A*");
			ImGui::NewLine();
			ImGui::TextWrapped("Clicking either the + or - buttons will increase/decrease the value by 10, or you can set the value manually, to a cap of 99.");
			ImGui::NewLine();
			ImGui::TextWrapped("Once a value has been set, right click anywhere to set that node's cost.");
			ImGui::NewLine();
			ImGui::TextWrapped("The higher the value, the darker that tile will appear.");
			ImGui::NewLine();
		}

		static void savingLoadingMaps()
		{
			ImGui::SeparatorText("Saving & Loading Maps");
			ImGui::TextWrapped("All saved maps are located in the folder: resources/maps");
			ImGui::NewLine();
			ImGui::TextWrapped("To save a map, set the name you wish to give to the map into the text field above the Save Map button.");
			ImGui::TextWrapped("Saved maps will contain the start node, goal node, closed nodes and any nodes costs.");
			ImGui::NewLine();
			ImGui::TextWrapped("Loading a map is done in the same way, input the name of the map, then hit the Load Map button.");
			ImGui::NewLine();
		}
	};
}