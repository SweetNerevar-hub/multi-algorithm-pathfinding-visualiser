#pragma once

#include "AlgorithmBase.h"

namespace mapv
{
	class AStar : public AlgorithmBase
	{
		struct TileCompare
		{
			bool operator()(const Tile* lhs, const Tile* rhs)
			{
				return lhs->f > rhs->f;
			}
		};

	public:
		enum Heuristic
		{
			EUCLIDIAN,
			OCTILE,
			CHEBYSHEV,
			MANHATTAN,
		};

		float weight = 1.f;
		Heuristic h = OCTILE;

	public:
		void init(Tile* start, Tile* end) override;
		void instantSearch() override;
		void visualiseSearch() override;

		AStar(VertexArray& tilesVA);

	private:
		std::priority_queue<Tile*, std::vector<Tile*>, TileCompare> m_prioQ;
		

	private:
		void runSearch() override;
		void cleanup() override;

		float heuristic(glm::vec2 origin, glm::vec2 dest);
		float euclidian(glm::vec2 origin, glm::vec2 dest);
		float octile(glm::vec2 origin, glm::vec2 dest);
		float chebyshev(glm::vec2 origin, glm::vec2 dest);
		float manhattan(glm::vec2 origin, glm::vec2 dest);
	};
}