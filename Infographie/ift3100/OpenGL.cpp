#include <GL\glew.h>
#include "OpenGL.h"

#include <iostream>

void OpenGL::initializeGL()
{	
	glewInit();

	glEnable(GL_DEPTH_TEST);
}

void OpenGL::paintGL()
{
	
	
}

