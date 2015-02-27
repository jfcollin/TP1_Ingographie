#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include <Primitives\ShapeData.h>

typedef unsigned int uint;

class ShapeGenerator
{
public:
	static ShapeData makeTriangle();
	static ShapeData makeCube();
	static ShapeData makePyramid();

};

#endif // SHAPEGENERATOR_H