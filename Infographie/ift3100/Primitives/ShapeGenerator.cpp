#include "ShapeGenerator.h"

#include <glm\glm.hpp>
#include <Primitives\Vertex.h>

#define NUM_ARRAY_ELEMENTS(x) sizeof(x) / sizeof(*x);

using glm::vec3;

ShapeData ShapeGenerator::makeTriangle()
{
	ShapeData out;

	Vertex triangle[] =
	{
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),

		vec3(+0.0f, +1.0f, +0.0f),
		vec3(+0.0f, +1.0f, +0.0f),

		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+0.0f, +0.0f, +1.0f),
	};

	out.numVertices = NUM_ARRAY_ELEMENTS(triangle);
	out.vertices = new Vertex[out.numVertices];
	memcpy(out.vertices, triangle, sizeof(triangle));

	GLushort indices[] = { 0, 1, 2 };
	out.numIndices = NUM_ARRAY_ELEMENTS(indices);
	out.indices = new GLushort[out.numIndices];
	memcpy(out.indices, indices, sizeof(indices));

	return out;
}

ShapeData ShapeGenerator::makeCube(){

	ShapeData out;
	
	Vertex stackVerts[] = {
		vec3(-1.0f, +1.0f, +1.0f), // 0
		vec3(+1.0f, +0.0f, +0.0f), // Colour
		vec3(+1.0f, +1.0f, +1.0f), // 1
		vec3(+0.0f, +1.0f, +0.0f), // Colour
		vec3(+1.0f, +1.0f, -1.0f), // 2
		vec3(+0.0f, +0.0f, +1.0f), // Colour
		vec3(-1.0f, +1.0f, -1.0f), // 3
		vec3(+1.0f, +1.0f, +1.0f), // Colour

		vec3(-1.0f, +1.0f, -1.0f), // 4
		vec3(+1.0f, +0.0f, +1.0f), // Colour
		vec3(+1.0f, +1.0f, -1.0f), // 5
		vec3(+0.0f, +0.5f, +0.2f), // Colour
		vec3(+1.0f, -1.0f, -1.0f), // 6
		vec3(+0.8f, +0.6f, +0.4f), // Colour
		vec3(-1.0f, -1.0f, -1.0f), // 7
		vec3(+0.3f, +1.0f, +0.5f), // Colour

		vec3(+1.0f, +1.0f, -1.0f), // 8
		vec3(+0.2f, +0.5f, +0.2f), // Colour
		vec3(+1.0f, +1.0f, +1.0f), // 9
		vec3(+0.9f, +0.3f, +0.7f), // Colour
		vec3(+1.0f, -1.0f, +1.0f), // 10
		vec3(+0.3f, +0.7f, +0.5f), // Colour
		vec3(+1.0f, -1.0f, -1.0f), // 11
		vec3(+0.5f, +0.7f, +0.5f), // Colour

		vec3(-1.0f, +1.0f, +1.0f), // 12
		vec3(+0.7f, +0.8f, +0.2f), // Colour
		vec3(-1.0f, +1.0f, -1.0f), // 13
		vec3(+0.5f, +0.7f, +0.3f), // Colour
		vec3(-1.0f, -1.0f, -1.0f), // 14
		vec3(+0.4f, +0.7f, +0.7f), // Colour
		vec3(-1.0f, -1.0f, +1.0f), // 15
		vec3(+0.2f, +0.5f, +1.0f), // Colour

		vec3(+1.0f, +1.0f, +1.0f), // 16
		vec3(+0.6f, +1.0f, +0.7f), // Colour
		vec3(-1.0f, +1.0f, +1.0f), // 17
		vec3(+0.6f, +0.4f, +0.8f), // Colour
		vec3(-1.0f, -1.0f, +1.0f), // 18
		vec3(+0.2f, +0.8f, +0.7f), // Colour
		vec3(+1.0f, -1.0f, +1.0f), // 19
		vec3(+0.2f, +0.7f, +1.0f), // Colour

		vec3(+1.0f, -1.0f, -1.0f), // 20
		vec3(+0.8f, +0.3f, +0.7f), // Colour
		vec3(-1.0f, -1.0f, -1.0f), // 21
		vec3(+0.8f, +0.9f, +0.5f), // Colour
		vec3(-1.0f, -1.0f, +1.0f), // 22
		vec3(+0.5f, +0.8f, +0.5f), // Colour
		vec3(+1.0f, -1.0f, +1.0f), // 23
		vec3(+0.9f, +1.0f, +0.2f), // Colour
	};

	out.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	out.vertices = new Vertex[out.numVertices];
	memcpy(out.vertices, stackVerts, sizeof(stackVerts));

	GLushort stackIndices[] = {
		 0,  1,  2,  0,  2,  3, // Top
		 4,  5,  6,  4,  6,  7, // Front
		 8,  9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};

	out.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	out.indices = new GLushort[out.numIndices];
	memcpy(out.indices, stackIndices, sizeof(stackIndices));

	return out;
}
