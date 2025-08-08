#include "Dijkstra.h"

mapv::Dijkstra::Dijkstra(VertexArray& tilesVA) : AlgorithmBase(tilesVA)
{
}

void mapv::Dijkstra::init(Tile* start, Tile* end)
{
	if (start == nullptr || end == nullptr)
	{
		std::cerr << "Couldn't find a starting/goal tile" << std::endl;
		return;
	}

	m_start = start;
	m_end = end;

	/* I'll just reuse the A*'s f value in place of Dijkstra's traversal value */
	m_start->f = 0;

	m_start->isVisited = true;
	m_prioQ.push(m_start);

	m_isSearching = true;
	m_searchTime = 0.f;
	m_nodesSearched = 0;
	m_pathLength = 0;
}

void mapv::Dijkstra::instantSearch()
{
	Clock dijkstraTime;

	while (!m_prioQ.empty())
		runSearch();

	m_searchTime = dijkstraTime.getTime().millisecondsf();
}

void mapv::Dijkstra::visualiseSearch()
{
	if (!m_prioQ.empty())
		runSearch();
}

void mapv::Dijkstra::runSearch()
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
		if (nbr == m_end)
		{
			nbr->parent = current;
			tracePath(nbr, m_start);
			return;
		}

		if (nbr->isVisited)
			continue;

		float traverseCost = current->cost + nbr->cost;
		if (nbr->f > current->f + traverseCost)
		{
			nbr->f = distance(current->getPos(), nbr->getPos()) + current->f + traverseCost;
			nbr->isVisited = true;
			nbr->parent = current;
			nbr->setType(m_tilesVA, QUEUED);

			m_prioQ.push(nbr);
			m_nodesSearched++;
		}
	}
}

void mapv::Dijkstra::cleanup()
{
	m_isSearching = false;
	m_start = nullptr;
	m_end = nullptr;

	while (!m_prioQ.empty())
		m_prioQ.pop();
}

float mapv::Dijkstra::distance(glm::vec2 origin, glm::vec2 dest)
{
	float dx = (dest.x - origin.x) * (dest.x - origin.x);
	float dy = (dest.y - origin.y) * (dest.y - origin.y);

	return std::sqrtf(dx + dy);
}
