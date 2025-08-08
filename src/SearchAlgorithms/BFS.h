#pragma once

#include "AlgorithmBase.h"

namespace mapv
{
	class BFS : public AlgorithmBase
	{
	public:
		void init(Tile* start, Tile* end) override;
		void instantSearch() override;
		void visualiseSearch() override;

		BFS(VertexArray& tilesVA);

	private:
		std::queue<Tile*> m_queue;

	private:
		void runSearch() override;
		void cleanup() override;
	};
}