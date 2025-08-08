#pragma once

#include <queue>

#include "../Utils/Audio.h"
#include "../Utils/Time.h"
#include "../Tile.h"
#include "../VertexArray.h"

namespace mapv
{
	class AlgorithmBase
	{
	public:
		virtual void init(Tile* start, Tile* end) = 0;
		virtual void instantSearch() = 0;
		virtual void visualiseSearch() = 0;
		void cancelSearch()
		{
			cleanup();
		}

		const int nodesSearched() const { return m_nodesSearched; }
		const int pathLength() const	{ return m_pathLength; }
		const float searchTime() const	{ return m_searchTime; }
		const bool isSearching() const	{ return m_isSearching; }

		AlgorithmBase(VertexArray& tilesVA) : m_tilesVA(tilesVA) { }
		virtual ~AlgorithmBase() = default;

	protected:
		virtual void runSearch() = 0;
		virtual void cleanup() = 0;
		void tracePath(Tile* current, Tile* start)
		{
			Audio::get().playSound(Audio::PATHFINDING_COMPLETE);

			while (current != start)
			{
				if (current != m_end)
					current->setType(m_tilesVA, PATH);

				current = current->parent;
				m_pathLength++;
			}

			cleanup();
		}

	protected:
		Tile*			m_start = nullptr;
		Tile*			m_end = nullptr;
		VertexArray&	m_tilesVA;
		float			m_searchTime = 0.f;
		int				m_nodesSearched = 0;
		int				m_pathLength = 0;
		bool			m_isSearching = false;
	};
}