#ifndef ANIMATION1_H
#define ANIMATION1_H

#include "OpenGL.h"

class Animation1 : public OpenGL
{
protected:
	void initializeGL();
	virtual void paintGL();

public:
	Animation1(QWidget *parent) : OpenGL(parent) {}
	~Animation1();
};

#endif // !ANIMATION1_H