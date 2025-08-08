#pragma once

#include <glm/glm.hpp>
#include "Utils/Colour.h"

namespace mapv
{
	struct Vertex
	{
		glm::vec2 position;
		Colour colour;

		Vertex() : position(0, 0), colour(1, 1, 1, 1) { }
		Vertex(glm::vec2 pos, Colour colour) : 
			position(pos),
			colour(colour) { }
	};
}