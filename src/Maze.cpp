#include "Maze.h"

namespace mapv
{
	Maze::Maze(VertexArray& tilesVA, std::vector<Tile>& tiles, u16 width) :
		m_tilesVA(tilesVA),
		m_tiles(tiles),
		m_mapWidth(width)
	{
	}

	void Maze::generate()
	{
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<size_t> dist(0, m_tiles.size());

		size_t randNum = dist(engine);

		m_tiles[randNum].isVisited = true;
		m_stack.push(&m_tiles[randNum]);

		while (!m_stack.empty())
		{
			Tile* current = m_stack.top();
			m_stack.pop();

			current->setType(m_tilesVA, EMPTY);

			for (Tile* nbr : current->neighbours)
			{
				if (nbr->isVisited)
					continue;

				m_stack.push(current);

				Tile* randNbr = chooseRandomNeighbour(current);
				randNbr->setType(m_tilesVA, EMPTY);
				randNbr->isVisited = true;

				m_stack.push(randNbr);

				removeWall(*current, *randNbr);

				break;
			}
		}

		fillBorder();
	}

	void Maze::setupMap()
	{
		for (u16 i = 0; i < m_tiles.size(); i++)
		{
			m_tiles[i].setType(m_tilesVA, WALL);
		}
	}

	void Maze::setNeighbours()
	{
		u16 widthIndex = 0;
		for (u16 i = 0; i < m_tiles.size(); i++)
		{
			/* Up */
			u16 targetTileIndex = i - (m_mapWidth * 2);
			if (targetTileIndex > 0 && targetTileIndex < m_tiles.size())
				m_tiles[i].neighbours.emplace_back(&m_tiles[i - (m_mapWidth * 2)]);

			/* Down */
			if (i + (m_mapWidth * 2) < m_tiles.size())
				m_tiles[i].neighbours.emplace_back(&m_tiles[i + (m_mapWidth * 2)]);

			/* Left */
			if (widthIndex > 1)
				m_tiles[i].neighbours.emplace_back(&m_tiles[i - 2]);

			/* Right */
			if (widthIndex < (m_mapWidth - 2))
				m_tiles[i].neighbours.emplace_back(&m_tiles[i + 2]);

			if (widthIndex++ == m_mapWidth - 1)
				widthIndex = 0;
		}
	}

	Tile* Maze::chooseRandomNeighbour(Tile* current)
	{
		std::random_device rd;
		std::shuffle(current->neighbours.begin(), current->neighbours.end(), std::default_random_engine(rd()));

		return current->neighbours.back();
	}

	void Maze::removeWall(Tile& current, Tile& neighbour)
	{
		if (neighbour.vaIndex == current.vaIndex - m_mapWidth * 2)
			m_tiles[current.vaIndex - m_mapWidth].setType(m_tilesVA, EMPTY);

		else if (neighbour.vaIndex == current.vaIndex + m_mapWidth * 2)
			m_tiles[current.vaIndex + m_mapWidth].setType(m_tilesVA, EMPTY);

		else if (neighbour.vaIndex == current.vaIndex - 2)
			m_tiles[current.vaIndex - 1].setType(m_tilesVA, EMPTY);

		else if (neighbour.vaIndex == current.vaIndex + 2)
			m_tiles[current.vaIndex + 1].setType(m_tilesVA, EMPTY);
	}

	void Maze::fillBorder()
	{
		for (u16 i = 0; i < m_tiles.size(); i++)
		{
			if (i < m_mapWidth || i > m_tiles.size() - m_mapWidth)
				m_tiles[i].setType(m_tilesVA, WALL);

			else if (i % m_mapWidth == 0 || i % m_mapWidth == m_mapWidth - 1)
				m_tiles[i].setType(m_tilesVA, WALL);
		}
	}
}