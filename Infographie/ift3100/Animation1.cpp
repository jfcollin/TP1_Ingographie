#include <iostream>
#include "Animation1.h"


Animation1::~Animation1()
{
}

void Animation1::initializeGL()
{
}

void Animation1::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}
