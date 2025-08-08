#include "AStar.h"

namespace mapv
{
	AStar::AStar(VertexArray& tilesVA) : AlgorithmBase(tilesVA)
	{
	}

	void AStar::init(Tile* start, Tile* end)
	{
		if (start == nullptr || end == nullptr)
		{
			std::cerr << "Couldn't find a starting/goal tile" << std::endl;
			return;
		}

		m_start = start;
		m_end = end;

		m_start->g = 0.f;
		m_start->f = heuristic(m_start->getPos(), m_end->getPos());

		m_start->isVisited = true;
		m_prioQ.push(m_start);

		m_isSearching = true;
		m_searchTime = 0.f;
		m_nodesSearched = 0;
		m_pathLength = 0;
	}

	void AStar::instantSearch()
	{
		Clock aStarTime;

		while (!m_prioQ.empty())
			runSearch();

		m_searchTime = aStarTime.getTime().millisecondsf();
	}

	void AStar::visualiseSearch()
	{
		if (!m_prioQ.empty())
		{
			runSearch();
			return;
		}

		m_isSearching = false;
	}

	void AStar::runSearch()
	{
		Tile* current = m_prioQ.top();
		m_prioQ.pop();

		if (current == m_end)
		{
			tracePath(current, m_start);
			return;
		}

		if (current != m_start)
			current->setType(m_tilesVA, VISITED);

		for (Tile* nbr : current->neighbours)
		{
			if (nbr == current->parent)
				continue;

			float traverseCost = heuristic(current->getPos(), nbr->getPos()) + (current->cost + nbr->cost);
			float possibleLowerGoal = current->g + traverseCost;

			if (possibleLowerGoal < nbr->g)
			{
				nbr->parent = current;
				nbr->g = possibleLowerGoal;

				if (nbr == m_end)
				{
					tracePath(nbr, m_start);
					return;
				}

				if (!nbr->isVisited)
				{
					nbr->f = possibleLowerGoal + heuristic(nbr->getPos(), m_end->getPos()) * weight;
					nbr->setType(m_tilesVA, QUEUED);
					nbr->isVisited = true;

					m_prioQ.push(nbr);
					m_nodesSearched++;
				}
			}
		}
	}

	void AStar::cleanup()
	{
		m_isSearching = false;
		m_start = nullptr;
		m_end = nullptr;

		while (!m_prioQ.empty())
			m_prioQ.pop();
	}

	float AStar::heuristic(glm::vec2 origin, glm::vec2 dest)
	{
		switch (h)
		{
		case EUCLIDIAN:
			return euclidian(origin, dest);

		case OCTILE:
			return octile(origin, dest);

		case CHEBYSHEV:
			return chebyshev(origin, dest);

		case MANHATTAN:
			return manhattan(origin, dest);

		default:
			return 0;
		}
	}

	float AStar::euclidian(glm::vec2 origin, glm::vec2 dest)
	{
		float dx = (dest.x - origin.x) * (dest.x - origin.x);
		float dy = (dest.y - origin.y) * (dest.y - origin.y);

		return std::sqrtf(dx + dy);
	}

	float AStar::octile(glm::vec2 origin, glm::vec2 dest)
	{
		float dx = std::abs(origin.x - dest.x);
		float dy = std::abs(origin.y - dest.y);

		/* 0.41f is the diagonal distance between tiles (1.41f) - 1 (distance to move cardinally) */
		return std::max(dx, dy) + (0.41f * std::min(dx, dy));
	}

	float AStar::chebyshev(glm::vec2 origin, glm::vec2 dest)
	{
		float dx = std::abs(origin.x - dest.x);
		float dy = std::abs(origin.y - dest.y);

		return std::max(dx, dy) + std::min(dx, dy);
	}

	float AStar::manhattan(glm::vec2 origin, glm::vec2 dest)
	{
		float dx = origin.x - dest.x;
		float dy = origin.y - dest.y;

		return dx + dy;
	}
}