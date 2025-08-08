#pragma once

#include <imgui/imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <vector>
#include <filesystem>
#include <fstream>

#include "Utils/Typedefs.h"
#include "Utils/Time.h"
#include "Tile.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Maze.h"

namespace mapv
{
	class Map
	{
	public:
		void draw(Shader shader);
		void updateGUI();
		void setTileType(GLFWwindow* window, double mx, double my, bool isLeftMouseInput);
		void clearMap(bool isSearchCancelled);
		void findNeighbours();

		void saveMap(const std::string& mapName);
		void loadMap(const std::string& mapName);

		Tile* getStartTile();
		Tile* getGoalTile();

		bool showGrid = true;

		Map(VertexArray& tilesVA);

	private:
		std::vector<Tile> m_tiles;
		VertexArray& m_tilesVA;
		VertexArray m_gridLines; 

		std::filesystem::path m_path = std::filesystem::current_path().append("resources/maps/");

		u16 m_width = 0;
		u16 m_height = 0;
		u16 m_tileSize = 0;

	private:
		void plotGridLines();
		void buildMap();

		void checkCardinal(u16 index, u16 widthIndex, bool* isDirOpen);
		void checkDiagonal(u16 index, u16 widthIndex, bool* isDirOpen);
	};
}