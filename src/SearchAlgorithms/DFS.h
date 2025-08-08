#pragma once

#include <stack>

#include "AlgorithmBase.h"

namespace mapv
{
	class DFS : public AlgorithmBase
	{
	public:
		DFS(VertexArray& tilesVA);

		void init(Tile* start, Tile* end) override;
		void instantSearch() override;
		void visualiseSearch() override;

	private:
		std::stack<Tile*> m_stack;

	private:
		void runSearch() override;
		void cleanup() override;

		void recursive(Tile* current);
	};
}