#include "DFS.h"

namespace mapv
{
	DFS::DFS(VertexArray& tilesVA) : AlgorithmBase(tilesVA)
	{
	}

	void DFS::init(Tile* start, Tile* end)
	{
		if (start == nullptr || end == nullptr)
		{
			std::cerr << "Couldn't find a starting/goal tile" << std::endl;
			return;
		}

		m_start = start;
		m_end = end;

		m_start->isVisited = true;
		m_stack.push(m_start);

		m_isSearching = true;
		m_searchTime = 0.f;
		m_nodesSearched = 0;
		m_pathLength = 0;
	}

	void DFS::instantSearch()
	{
		Clock dfsTime;

		while (!m_stack.empty())
			runSearch();

		m_searchTime = dfsTime.getTime().millisecondsf();
	}

	void DFS::visualiseSearch()
	{
		if (!m_stack.empty())
			runSearch();
	}

	void DFS::runSearch()
	{
		Tile* current = m_stack.top();
		m_stack.pop();

		if (current == m_end)
		{
			tracePath(current, m_start);
			return;
		}

		if (current != m_start)
			current->setType(m_tilesVA, VISITED);

		for (Tile* nbr : current->neighbours)
		{
			if (nbr->isVisited)
				continue;

			if (nbr == m_end)
			{
				tracePath(current, m_start);
				return;
			}

			nbr->setType(m_tilesVA, QUEUED);
			nbr->parent = current;
			nbr->isVisited = true;

			m_stack.push(nbr);
			m_nodesSearched++;
		}
	}

	void DFS::cleanup()
	{
		m_isSearching = false;
		m_start = nullptr;
		m_end = nullptr;

		while (!m_stack.empty())
			m_stack.pop();
	}

	void DFS::recursive(Tile* current)
	{
		current->isVisited = true;
		current->setType(m_tilesVA, VISITED);
		for (Tile* nbr : current->neighbours)
		{
			if (!nbr->isVisited)
			{
				m_stack.push(nbr);
				nbr->setType(m_tilesVA, QUEUED);
				recursive(nbr);
			}
		}
	}
}