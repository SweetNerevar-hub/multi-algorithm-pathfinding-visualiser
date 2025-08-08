#include "Tile.h"


namespace mapv
{
	Tile::Tile(glm::vec2 pos, f32 width, f32 height)
	{
		m_vertices.resize(6);

		float x = (pos.x * width);
		float y = (pos.y * height);

		m_vertices[0].position = { x, y };
		m_vertices[1].position = { x, y + height };
		m_vertices[2].position = { x + width, y };
		m_vertices[3].position = { x + width, y };
		m_vertices[4].position = { x, y + height };
		m_vertices[5].position = { x + width, y + height };

		Colour empty = { 0.35f, 0.21f, 0.43f, alphaByCost() };
		for (int i = 0; i < m_vertices.size(); i++)
		{
			m_vertices[i].colour = empty;
		}
	}

	const std::vector<Vertex> Tile::getVertices()
	{
		return m_vertices;
	}

	void Tile::setType(VertexArray& tilesVA, Type type)
	{
		this->type = type;
		switch (type)
		{
		case EMPTY:
		{
			Colour empty;
			empty = { 0.35f, 0.21f, 0.43f, alphaByCost() };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = empty;
				tilesVA[vaIndex * 6 + i].colour = empty;
			}
			break;
		}

		case WALL:
		{
			Colour wall;
			wall = { 0.78f, 0.78f, 0.78f };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = wall;
				tilesVA[vaIndex * 6 + i].colour = wall;
			}
			break;
		}

		case START:
		{
			Colour start;
			start = { 0.33f, 0.62f, 0.29f };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = start;
				tilesVA[vaIndex * 6 + i].colour = start;
			}
			break;
		}

		case GOAL:
		{
			Colour goal;
			goal = { 0.62f, 0.29f, 0.29f };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = goal;
				tilesVA[vaIndex * 6 + i].colour = goal;
			}
			break;
		}

		case VISITED:
		{
			Colour visited;
			visited = { 0.29f, 0.55f, 0.62f, alphaByCost() };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = visited;
				tilesVA[vaIndex * 6 + i].colour = visited;
			}
			break;
		}
			
		case PATH:
		{
			Colour path;
			path = { 0.61f, 0.62f, 0.29f };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = path;
				tilesVA[vaIndex * 6 + i].colour = path;
			}
			break;
		}	

		case QUEUED:
		{
			Colour queued;
			queued = { 0.20f, 0.76f, 0.78f, alphaByCost() };

			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = queued;
				tilesVA[vaIndex * 6 + i].colour = queued;
			}

			break;
		}	

		default:
			for (int i = 0; i < m_vertices.size(); i++)
			{
				m_vertices[i].colour = Colour::black();
				tilesVA[vaIndex * 6 + i].colour = Colour::black();
			}
			break;
		}
	}

	const glm::vec2 Tile::getPos() const
	{
		return m_vertices[0].position;
	}

	float Tile::alphaByCost()
	{
		if (cost == 0)
			return 1.f;

		return 1.f - (cost / 100.f);
	}
}