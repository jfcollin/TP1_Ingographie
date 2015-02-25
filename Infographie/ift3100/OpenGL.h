#ifndef OPENGL_H
#define OPENGL_H

#include <qopenglwidget.h>


class OpenGL : public QOpenGLWidget
{
protected:
	void initializeGL();
	virtual void paintGL();

public:
	OpenGL(QWidget *parent) : QOpenGLWidget(parent) {}
	virtual ~OpenGL() {}
};

#endif // !OPENGL_H