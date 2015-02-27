#ifndef ANIMATION2_H
#define ANIMATION2_H

#include "OpenGL.h"

class Animation2 : public OpenGL
{
protected:
	virtual void initializeGL();
	virtual void paintGL();
	void installerShader();
	void envoyerData();

public:
	Animation2(QWidget *parent) : OpenGL(parent) {}
	~Animation2();
	void enregistrerImage();
};

#endif // !ANIMATION2_H