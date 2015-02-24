#include <iostream>
#include "Animation2.h"


Animation2::~Animation2()
{
}

void Animation2::initializeGL()
{
}

void Animation2::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
}