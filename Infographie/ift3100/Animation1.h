#ifndef ANIMATION1_H
#define ANIMATION1_H

#include "OpenGL.h"
#include <qtimer.h>

class Animation1 : public OpenGL
{
protected:
	void initializeGL();
	virtual void paintGL();
	void sendDataToOpenGL();
	void installShaders();

public:
	Animation1(QWidget *parent) : OpenGL(parent), mDrawTimer(this) {}
	~Animation1();
private:
	QTimer mDrawTimer;
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgramStatus(GLuint programID);
	std::string readShaderCode(const char* fileName);
};

#endif // !ANIMATION1_H