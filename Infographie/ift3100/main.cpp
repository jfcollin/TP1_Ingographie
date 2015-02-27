#include <GL\glew.h>
#include <QtWidgets/QApplication>
#include "Window.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Window w;
	w.show();

	/*// Initialisation de GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// glewInit ne fonctionne pas...
		fprintf(stderr, "Erreur: %s\n", glewGetErrorString(err));
	}

	// Vérification de la version d'OpenGL
	if (!GLEW_VERSION_2_1)
	{
		fprintf(stderr, "OpenGL 2.1 non supporté\n");
	}*/


	return a.exec();
}
