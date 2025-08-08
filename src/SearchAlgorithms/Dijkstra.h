#pragma once

#include "AlgorithmBase.h"

namespace mapv
{
	class Dijkstra : public AlgorithmBase
	{
		struct TileCompare
		{
			bool operator()(const Tile* lhs, const Tile* rhs)
			{
				return lhs->f > rhs->f;
			}
		};

	public:
		Dijkstra(VertexArray& tilesVA);

		void init(Tile* start, Tile* end) override;
		void instantSearch() override;
		void visualiseSearch() override;

	private:
		std::priority_queue<Tile*, std::vector<Tile*>, TileCompare> m_prioQ;

	private:
		void runSearch() override;
		void cleanup() override;

		float distance(glm::vec2 origin, glm::vec2 dest);
	};
}