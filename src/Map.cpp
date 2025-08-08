#include "Map.h"

#include "GUI/GUI_NodeCost.h"

namespace mapv
{
	Map::Map(VertexArray& tilesVA) :
		m_tilesVA(tilesVA)
	{
	}

	void Map::updateGUI()
	{
		ImGui::SeparatorText("Map Generator");

		int w = static_cast<int>(m_width);
		int h = static_cast<int>(m_height);
		int tileSize = static_cast<int>(m_tileSize);

		if (ImGui::InputInt("Map Width", &w))
		{
			if (w > 128)
				w = 128;

			m_width = w;
			plotGridLines();
			buildMap();
		}

		else if (ImGui::InputInt("Map Height", &h))
		{
			if (h > 128)
				h = 128;

			m_height = h;
			plotGridLines();
			buildMap();
		}

		else if (ImGui::InputInt("Tile Size", &tileSize))
		{
			m_tileSize = tileSize;
			plotGridLines();
			buildMap();
		}

		else if (ImGui::Button("Generate Maze"))
		{
			if (m_tiles.empty())
				return;

			clearMap(false);
			Maze maze(m_tilesVA, m_tiles, m_width);
			maze.setupMap();
			maze.setNeighbours();
			maze.generate();

			for (Tile& t : m_tiles)
			{
				t.isVisited = false;
				t.neighbours.clear();
			}
		}

		ImGui::Checkbox("Show Grid", &showGrid);
		ImGui::NewLine();
	}

	void Map::setTileType(GLFWwindow* window, double mx, double my, bool isLeftMouseInput)
	{
		u16 mapWidth = m_width * m_tileSize;
		u16 mapHeight = m_height * m_tileSize;
		bool isMouseOutsideMapBounds = (mx >= mapWidth || mx <= 0) || (my >= mapHeight || my <= 0);
		if (isMouseOutsideMapBounds)
			return;

		mx = std::trunc(mx) / m_tileSize;
		my = std::trunc(my) / m_tileSize;

		Tile& selectedTile = m_tiles[(u16)mx + (u16)my * m_width];

		/* If the right mouse button is pressed/held */
		if (!isLeftMouseInput)
		{
			selectedTile.cost = (float)GUI_NodeCost::getCostValue();
			selectedTile.setType(m_tilesVA, EMPTY);
		}

		else
		{
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				Tile* tile = getStartTile();

				/* If a start tile already exists, replace it with the new position */
				if (tile != nullptr)
					tile->setType(m_tilesVA, EMPTY);

				selectedTile.setType(m_tilesVA, START);
			}

			else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
			{
				Tile* tile = getGoalTile();

				/* If a goal tile already exists, replace it with the new position */
				if (tile != nullptr)
					tile->setType(m_tilesVA, EMPTY);

				selectedTile.setType(m_tilesVA, GOAL);
			}

			else
				selectedTile.setType(m_tilesVA, WALL);
		}
	}

	void Map::clearMap(bool isSearchCancelled)
	{
		for (u16 i = 0; i < m_tiles.size(); i++)
		{
			Tile& tile = m_tiles[i];

			tile.cost = 0.f;
			tile.f = INFINITY;
			tile.g = INFINITY;
			
			tile.isVisited = false;
			tile.neighbours.clear();
			tile.parent = nullptr;

			if (isSearchCancelled && tile.type > 3)
			{
				tile.setType(m_tilesVA, EMPTY);
				for (u16 j = 0; j < 6; j++)
				{
					m_tilesVA[tile.vaIndex * 6 + j].colour = tile.getVertices()[0].colour;
				}
			}

			else if (!isSearchCancelled)
			{
				tile.setType(m_tilesVA, EMPTY);
				for (u16 j = 0; j < 6; j++)
				{
					m_tilesVA[tile.vaIndex * 6 + j].colour = tile.getVertices()[0].colour;
				}
			}
		}
	}

	void Map::plotGridLines()
	{
		if (m_gridLines.length() > 0)
			m_gridLines.clear();

		for (u16 i = 1; i < m_width; i++)
		{
			Vertex vTop;
			vTop.position = glm::vec2{ i * m_tileSize, 0.f };
			vTop.colour = Colour::black();

			Vertex vBot;
			vBot.position = glm::vec2{ i * m_tileSize, m_height * m_tileSize };
			vBot.colour = Colour::black();

			m_gridLines.appendVertex(vTop);
			m_gridLines.appendVertex(vBot);
		}

		for (u16 i = 1; i < m_height; i++)
		{
			Vertex vLeft;
			vLeft.position = glm::vec2{ 0.f, i * m_tileSize };
			vLeft.colour = Colour::black();

			Vertex vRight;
			vRight.position = glm::vec2{ m_width * m_tileSize, i * m_tileSize };
			vRight.colour = Colour::black();

			m_gridLines.appendVertex(vLeft);
			m_gridLines.appendVertex(vRight);
		}
	}

	void Map::draw(Shader shader)
	{
		m_tilesVA.draw(shader, GL_TRIANGLES);

		if (showGrid)
			m_gridLines.draw(shader, GL_LINES);
	}

	void Map::buildMap()
	{
		if (m_tiles.size() > 0)
		{
			m_tiles.clear();
			m_tilesVA.clear();
		}

		for (u16 y = 0; y < m_height; y++)
		{
			for (u16 x = 0; x < m_width; x++)
			{
				Tile tile{ glm::vec2{ (f32)x, (f32)y }, (f32)m_tileSize, (f32)m_tileSize };

				m_tilesVA.appendArray(tile.getVertices());

				tile.vaIndex = (u32)m_tilesVA.length() / 6 - 1;
				m_tiles.emplace_back(tile);
			}
		}
	}

	void Map::findNeighbours()
	{
		u16 widthIndex = 0;

		for (u16 i = 0; i < m_tiles.size(); i++)
		{
			/*
			Faster/easier way to know while checking the cardinal tiles:
			are those tiles open? and send that info to the diagonal checks
			to gauge whether or not to allow a diagonal tile to become a neighbour
			*/
			bool isDirOpen[4] = { false, false, false, false };

			checkCardinal(i, widthIndex, isDirOpen);
			checkDiagonal(i, widthIndex, isDirOpen);

			if (widthIndex++ < m_width - 1)
				continue;

			widthIndex = 0;
		}
	}

	void Map::saveMap(const std::string& mapName)
	{
		if (m_tiles.size() == 0)
			return;

		std::ofstream file(m_path.string() + mapName);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file!" << std::endl;
			std::cerr << "PATH: " << m_path.string() + mapName << std::endl;
			return;
		}

		nlohmann::json data;
		data["map_width"] = m_width;
		data["map_height"] = m_height;
		data["tile_size"] = m_tileSize;

		int index = 0;
		for (const Tile& tile : m_tiles)
		{
			/* Only serialize open, closed, start and goal nodes */
			if (tile.type <= 3)
			{
				data[std::to_string(index)] = {
					{ "type", tile.type },
					{ "cost", tile.cost }
				};
			}

			index++;
		}

		std::vector<std::uint8_t> cbor = nlohmann::json::to_cbor(data);
		for (int i = 0; i < cbor.size(); i++)
		{
			file << cbor[i];
		}

		file.close();
	}

	void Map::loadMap(const std::string& mapName)
	{
		if (!std::filesystem::exists(m_path.string() + mapName))
		{
			std::cerr << "File does not exist!" << std::endl;
			std::cerr << "PATH: " << m_path.string() + mapName << std::endl;
			return;
		}

		std::ifstream file(m_path.string() + mapName);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file!" << std::endl;
			std::cerr << "PATH: " << m_path.string() + mapName << std::endl;
			return;
		}

		nlohmann::json data = nlohmann::json::from_cbor(file);

		m_width = data["map_width"];
		m_height = data["map_height"];
		m_tileSize = data["tile_size"];

		if (m_tiles.size() > 0)
		{
			m_tiles.clear();
			m_tilesVA.clear();
		}

		int index = 0;
		for (u16 y = 0; y < m_height; y++)
		{
			for (u16 x = 0; x < m_width; x++)
			{
				std::string idx = std::to_string(index);

				Tile tile{ glm::vec2{ (f32)x, (f32)y }, (f32)m_tileSize, (f32)m_tileSize };
				m_tilesVA.appendArray(tile.getVertices());

				tile.vaIndex = (u32)m_tilesVA.length() / 6 - 1;
				tile.cost = data[idx]["cost"];
				tile.setType(m_tilesVA, (Type)data[idx]["type"]);

				m_tiles.emplace_back(tile);

				index++;
			}
		}

		if (showGrid)
			plotGridLines();
	}

	void Map::checkCardinal(u16 index, u16 widthIndex, bool* isDirOpen)
	{
		/* Up */
		if (index - m_width > 0 && index - m_width < m_tiles.size() && m_tiles[index - m_width].type != WALL)
		{
			isDirOpen[0] = true;
			m_tiles[index].neighbours.emplace_back(&m_tiles[index - m_width]);
		}

		/* Down */
		if (index + m_width < m_tiles.size() && m_tiles[index + m_width].type != WALL)
		{
			isDirOpen[1] = true;
			m_tiles[index].neighbours.emplace_back(&m_tiles[index + m_width]);
		}

		/* Left */
		if (widthIndex > 0 && m_tiles[index - 1].type != WALL)
		{
			isDirOpen[2] = true;
			m_tiles[index].neighbours.emplace_back(&m_tiles[index - 1]);
		}

		/* Right */
		if (widthIndex < (m_width - 1) && m_tiles[index + 1].type != WALL)
		{
			isDirOpen[3] = true;
			m_tiles[index].neighbours.emplace_back(&m_tiles[index + 1]);
		}	
	}

	void Map::checkDiagonal(u16 index, u16 widthIndex, bool* isDirOpen)
	{
		int targetTileIdx = 0;

		/* Up-Left */
		targetTileIdx = index - (m_width + 1);
		if (widthIndex > 0 && targetTileIdx > 0 && m_tiles[targetTileIdx].type != WALL)
		{
			if (isDirOpen[0] && isDirOpen[2])
				m_tiles[index].neighbours.emplace_back(&m_tiles[targetTileIdx]);
		}

		/* Up-Right */
		targetTileIdx = index - (m_width - 1);
		if (targetTileIdx > 0 && m_tiles[targetTileIdx].type != WALL)
		{
			if (isDirOpen[0] && isDirOpen[3])
				m_tiles[index].neighbours.emplace_back(&m_tiles[targetTileIdx]);
		}

		/* Down-Left */
		targetTileIdx = index + (m_width - 1);
		if (widthIndex > 0 && targetTileIdx < m_tiles.size() && m_tiles[targetTileIdx].type != WALL)
		{
			if (isDirOpen[1] && isDirOpen[2])
				m_tiles[index].neighbours.emplace_back(&m_tiles[targetTileIdx]);
		}

		/* Down-Right */
		targetTileIdx = index + (m_width + 1);
		if (targetTileIdx < m_tiles.size() && m_tiles[targetTileIdx].type != WALL)
		{
			if (isDirOpen[1] && isDirOpen[3])
				m_tiles[index].neighbours.emplace_back(&m_tiles[targetTileIdx]);
		}
	}

	Tile* Map::getStartTile()
	{
		for (u16 y = 0; y < m_height; y++)
		{
			for (u16 x = 0; x < m_width; x++)
			{
				Tile& current = m_tiles[x + y * m_width];
				if (current.type == START)
					return &current;
			}
		}
		return nullptr;
	}

	Tile* Map::getGoalTile()
	{
		for (u16 y = 0; y < m_height; y++)
		{
			for (u16 x = 0; x < m_width; x++)
			{
				Tile& current = m_tiles[x + y * m_width];
				if (current.type == GOAL)
					return &current;
			}
		}
		return nullptr;
	}
}