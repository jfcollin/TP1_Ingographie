#ifndef ANIMATION2_H
#define ANIMATION2_H

#include "OpenGL.h"

class Animation2 : public OpenGL
{
protected:
	void initializeGL();
	virtual void paintGL();

public:
	Animation2(QWidget *parent) : OpenGL(parent) {}
	~Animation2();
};

#endif // !ANIMATION2_H