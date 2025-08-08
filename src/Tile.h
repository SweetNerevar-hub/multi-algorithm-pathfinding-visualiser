#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Utils/Typedefs.h"
#include "Utils/Colour.h"
#include "Vertex.h"
#include "VertexArray.h"

namespace mapv
{
	enum Type
	{
		EMPTY,
		WALL,
		START,
		GOAL,
		VISITED,
		PATH,
		QUEUED
	};

	class Tile
	{
	public:
		std::vector<Tile*> neighbours;
		Tile* parent = nullptr;
		Type type = EMPTY;

		float cost = 0.f;
		float f = INFINITY;
		float g = INFINITY;

		u16 vaIndex = 0;
		bool isVisited = false;

	public:
		Tile(glm::vec2 pos, f32 width, f32 height);

		const std::vector<Vertex> getVertices();
		const glm::vec2 getPos() const;

		void setType(VertexArray& tilesVA, Type type);

	private:
		std::vector<Vertex> m_vertices;

	private:
		float alphaByCost();
	};
}