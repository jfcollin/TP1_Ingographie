#ifndef ANIMATION3_H
#define ANIMATION3_H

#include "OpenGL.h"

class Animation3 : public OpenGL
{
protected:
	virtual void initializeGL();
	virtual void paintGL();
	void installerShader();
	void envoyerData();

public:
	Animation3(QWidget *parent) : OpenGL(parent) {}
	~Animation3();
	void enregistrerImage();
};

#endif // !ANIMATION3_H
