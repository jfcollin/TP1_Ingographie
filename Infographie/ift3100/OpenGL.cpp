#include <GL\glew.h>
#include "OpenGL.h"


void OpenGL::initializeGL()
{	
	// Initialisation de GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// glewInit ne fonctionne pas...
		fprintf(stderr, "Erreur: %s\n", glewGetErrorString(err));
	}
	
}

void OpenGL::paintGL()
{
	
	
}

