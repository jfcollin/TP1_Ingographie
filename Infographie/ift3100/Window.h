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
	QMenu *fileMenu;
	QAction *exportAct1;
	QAction *exportAct2;
	QAction *exportAct3;
	QToolBar *fileToolBar;

private slots:
	void exporterScene1();
	void exporterScene2();
	void exporterScene3();
};

#endif // WINDOW_H
