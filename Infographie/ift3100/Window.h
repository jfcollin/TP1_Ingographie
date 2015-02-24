#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_Window.h"

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);
	~Window();

private:
	Ui::WindowClass ui;
};

#endif // WINDOW_H
