#ifndef VERTEX_H
#define VERTEX_H

#include <glm\glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinate;
	glm::vec4 color;

	// Offsets
	static size_t offsetNormal()
	{ 
		return sizeof(glm::vec3); 
	}
	
	static size_t offsetTextureCoordinate() 
	{ 
		return sizeof(glm::vec3) * 2; 
	}

	static size_t offsetColor()
	{
		return sizeof(glm::vec3) * 2 + sizeof(glm::vec2);
	}
};

#endif // VERTEX_H
