#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Utils/Typedefs.h"
#include "Vertex.h"
#include "Shader.h"

namespace mapv
{
	class VertexArray
	{
	public:
		void appendVertex(Vertex vertex);
		void appendArray(std::vector<Vertex> vertices);
		void draw(Shader shader, GLenum drawMode);

		void updateBuffer();
		void reserve(u64 capacity);
		void clear();
		const u64 length() const;

		VertexArray();
		~VertexArray();

		Vertex& operator[](u32 index);
		const Vertex& operator[](u32 index) const;

	private:
		std::vector<Vertex> m_vertices;

		u32 m_vao = 0;
		u32 m_vbo = 0;
	};
}