#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <GL\glew.h>
#include <Primitives\Vertex.h>

struct ShapeData
{
	ShapeData() : vertices(0), numVertices(0), indices(0), numIndices(0) {}

	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}

	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}

	void destroy()
	{
		delete[] vertices;
		delete[] indices;
		numVertices = 0;
		numIndices = 0;
	}
};

#endif // SHAPEDATA_H
