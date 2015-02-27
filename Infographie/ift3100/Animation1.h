#ifndef ANIMATION1_H
#define ANIMATION1_H

#include "OpenGL.h"

class Animation1 : public OpenGL
{
protected:
	virtual void initializeGL();
	virtual void paintGL();
	void installerShader();
	void envoyerData();

	void mouseMoveEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);

public:
	Animation1(QWidget *parent) : OpenGL(parent) {}
	~Animation1();
	void enregistrerImage();

private:
	std::string readShaderCode(const char* fileName);
};

#endif // !ANIMATION1_H