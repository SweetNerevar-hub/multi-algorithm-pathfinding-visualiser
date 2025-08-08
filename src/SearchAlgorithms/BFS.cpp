#include "BFS.h"

namespace mapv
{
	BFS::BFS(VertexArray& tilesVA) : AlgorithmBase(tilesVA) {}

	void BFS::init(Tile* start, Tile* end)
	{
		if (start == nullptr || end == nullptr)
		{
			std::cerr << "Couldn't find a starting/goal tile" << std::endl;
			return;
		}

		m_start = start;
		m_end = end;

		m_start->isVisited = true;
		m_queue.push(start);

		m_isSearching = true;
		m_searchTime = 0.f;
		m_nodesSearched = 0;
		m_pathLength = 0;
	}

	void BFS::instantSearch()
	{
		Clock bfsTime;

		while (!m_queue.empty())
			runSearch();

		m_searchTime = bfsTime.getTime().millisecondsf();
	}

	void BFS::visualiseSearch()
	{
		if (!m_queue.empty())
			runSearch();
	}

	void BFS::runSearch()
	{
		Tile* current = m_queue.front();
		m_queue.pop();

		if (current == m_end)
		{
			tracePath(current, m_start);
			return;
		}

		if (current != m_start)
			current->setType(m_tilesVA, VISITED);

		for (Tile* t : current->neighbours)
		{
			if (t == m_end)
			{
				tracePath(current, m_start);
				return;
			}

			if (t->isVisited)
				continue;

			t->parent = current;
			t->isVisited = true;
			t->setType(m_tilesVA, QUEUED);

			m_queue.push(t);

			m_nodesSearched++;
		}
	}

	void BFS::cleanup()
	{
		m_isSearching = false;
		m_start = nullptr;
		m_end = nullptr;

		while (!m_queue.empty())
			m_queue.pop();
	}
}