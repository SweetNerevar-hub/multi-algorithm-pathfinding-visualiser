#include "VertexArray.h"

namespace mapv
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		/* Position Attribute */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		/* Colour Attribute */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	void VertexArray::appendVertex(Vertex vertex)
	{
		m_vertices.emplace_back(vertex);
	}

	void VertexArray::appendArray(std::vector<Vertex> vertices)
	{
		for (Vertex v : vertices)
		{
			m_vertices.emplace_back(v);
		}
	}

	void VertexArray::draw(Shader shader, GLenum drawMode)
	{
		if (m_vertices.size() == 0)
			return;

		updateBuffer();
		glDrawArrays(drawMode, 0, (GLsizei)m_vertices.size());
	}

	void VertexArray::updateBuffer()
	{
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	}

	void VertexArray::reserve(u64 capacity)
	{
		m_vertices.reserve(capacity);
	}

	void VertexArray::clear()
	{
		m_vertices.clear();
	}

	const u64 VertexArray::length() const
	{
		return m_vertices.size();
	}

	Vertex& VertexArray::operator[](u32 index)
	{
		return m_vertices[index];
	}

	const Vertex& VertexArray::operator[](u32 index) const
	{
		return m_vertices[index];
	}
}