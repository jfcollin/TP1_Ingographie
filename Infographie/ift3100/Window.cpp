#include "Window.h"
#include <qfiledialog.h>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	exportAct1 = new QAction(QIcon(":/images/new.png"), tr("&Scene1"), this);
	exportAct2 = new QAction(QIcon(":/images/new.png"), tr("&Scene2"), this);
	exportAct3 = new QAction(QIcon(":/images/new.png"), tr("&Scene3"), this);
	connect(exportAct1, SIGNAL(triggered()), this, SLOT(exporterScene1()));
	connect(exportAct2, SIGNAL(triggered()), this, SLOT(exporterScene2()));
	connect(exportAct3, SIGNAL(triggered()), this, SLOT(exporterScene3()));
	
	fileMenu = menuBar()->addMenu(tr("&Exporter"));
	fileMenu->addAction(exportAct1);
	fileMenu->addAction(exportAct2);
	fileMenu->addAction(exportAct3);
	fileMenu->addSeparator();
	QKeySequence racourci1(Qt::CTRL + Qt::Key_1);
	QKeySequence racourci2(Qt::CTRL + Qt::Key_2);
	QKeySequence racourci3(Qt::CTRL + Qt::Key_3);
	exportAct1->setShortcut(racourci1);
	exportAct2->setShortcut(racourci2);
	exportAct3->setShortcut(racourci3);

	/*connect(ui.menuBar,&QMenu::,
		ui.openGLWidget, &Animation1::enregistrerImage);*/
}

Window::~Window()
{
	
}

void Window::exporterScene1()
{
	ui.openGLWidget->enregistrerImage();
	
}

void Window::exporterScene2()
{
	ui.openGLWidget_2->enregistrerImage();

}

void Window::exporterScene3()
{
	ui.openGLWidget_3->enregistrerImage();

}
