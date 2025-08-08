#pragma once

#include <stack>
#include <algorithm>
#include <random>
#include <chrono>

#include "Tile.h"

namespace mapv
{
	class Maze
	{
	public:
		void generate();
		void setupMap();
		void setNeighbours();

		Maze(VertexArray& tilesVA, std::vector<Tile>& tiles, u16 width);

	private:
		std::stack<Tile*> m_stack;
		std::vector<Tile>& m_tiles;
		VertexArray& m_tilesVA;
		u16 m_mapWidth;

	private:
		Tile* chooseRandomNeighbour(Tile* current);
		void removeWall(Tile& current, Tile& neighbour);
		void fillBorder();
	};
}