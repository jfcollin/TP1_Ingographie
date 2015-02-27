#include <GL\glew.h>
#include "OpenGL.h"

#include <iostream>

void OpenGL::initializeGL()
{	
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(3);
}

void OpenGL::paintGL()
{
	
	
}

