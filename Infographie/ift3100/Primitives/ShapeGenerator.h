#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include <Primitives\ShapeData.h>

class ShapeGenerator
{
public:
	static ShapeData makeTriangle();
	static ShapeData makeCube();
};

#endif // SHAPEGENERATOR_H