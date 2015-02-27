#include "ShapeGenerator.h"
#include <Primitives\Vertex.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#define PI 3.14159265359
#define NUM_ARRAY_ELEMENTS(x) sizeof(x) / sizeof(*x);

using glm::vec3;
using glm::mat3;
using glm::mat4;


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

ShapeData ShapeGenerator::makeCube()
{
	ShapeData out;
	
	Vertex cube[] = {

		vec3(+1.0f, -1.0f, +1.0f), // 0
		vec3(+1.0f, +0.0f, +0.0f), // Colour

		vec3(+1.0f, +1.0f, +1.0f), // 1
		vec3(+0.0f, +1.0f, +0.0f), // Colour

		vec3(-1.0f, +1.0f, +1.0f), // 2
		vec3(+0.0f, +0.0f, +1.0f), // Colour

		vec3(-1.0f, -1.0f, +1.0f), // 3
		vec3(+1.0f, +0.0f, +0.0f), // Colour

		vec3(+1.0f, -1.0f, -1.0f), // 4
		vec3(+0.0f, +0.0f, +1.0f), // Colour

		vec3(+1.0f, +1.0f, -1.0f), // 5
		vec3(+1.0f, +0.0f, +0.0f), // Colour

		vec3(-1.0f, +1.0f, -1.0f), // 6
		vec3(+0.0f, +0.0f, +1.0f), // Colour

		vec3(-1.0f, -1.0f, -1.0f), // 7
		vec3(+0.0f, +1.0f, +0.0f), // Colour

	};

	out.numVertices = NUM_ARRAY_ELEMENTS(cube);
	out.vertices = new Vertex[out.numVertices];
	memcpy(out.vertices, cube, sizeof(cube));


	    //6-------------/5
	  //  .           // |
	//2--------------1   |
	//    .          |   |
	//    .          |   |
	//    .          |   |
	//    .          |   |
	//    7.......   |   /4
	//               | //
	//3--------------/0

	GLushort indices[] = {

		0, 1, 2, 3,	//devant
		7, 6, 5, 4,	//derriere
		3, 2, 6, 7, //gauche
		4, 5, 1, 0, //droite
		1, 5, 6, 2, //dessus
		4, 0, 3, 7  //dessous

	};

	out.numIndices = NUM_ARRAY_ELEMENTS(indices);
	out.indices = new GLushort[out.numIndices];
	memcpy(out.indices, indices, sizeof(indices));

	return out;
}

ShapeData ShapeGenerator::makePyramid()
{
	ShapeData out;

	Vertex pyramide[] = {

		vec3(+1.0f, +0.0f, +1.0f), // 0
		vec3(+1.0f, +0.0f, +0.0f), // Colour

		vec3(+1.0f, +0.0f, -1.0f), // 1
		vec3(+0.0f, +1.0f, +0.0f), // Colour

		vec3(-1.0f, +0.0f, -1.0f), // 2
		vec3(+0.0f, +0.0f, +1.0f), // Colour

		vec3(-1.0f, +0.0f, +1.0f), // 3
		vec3(+1.0f, +0.0f, +0.0f), // Colour

		vec3(+0.0f, +1.0f, +0.0f), // 4
		vec3(+0.0f, +1.0f, +0.0f), // Colour
	};

	out.numVertices = NUM_ARRAY_ELEMENTS(pyramide);
	out.vertices = new Vertex[out.numVertices];
	memcpy(out.vertices, pyramide, sizeof(pyramide));

	GLushort indices[] = {

		0, 3, 4,  //devant
		1, 0, 4,  //droite
		2, 1, 4,  //derrière
		3, 2, 4,  //gauche
		2, 0, 3,  //dessous
		2, 1, 0,  //dessous

	};

	out.numIndices = NUM_ARRAY_ELEMENTS(indices);
	out.indices = new GLushort[out.numIndices];
	memcpy(out.indices, indices, sizeof(indices));

	return out;
}