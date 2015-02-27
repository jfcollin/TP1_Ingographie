#include "Window.h"
#include <qfiledialog.h>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	exportAct1 = new QAction(QIcon(":/images/new.png"), tr("&Scene1"), this);
	exportAct2 = new QAction(QIcon(":/images/new.png"), tr("&Scene2"), this);
	connect(exportAct1, SIGNAL(triggered()), this, SLOT(exporterScene1()));
	connect(exportAct2, SIGNAL(triggered()), this, SLOT(exporterScene2()));
	
	fileMenu = menuBar()->addMenu(tr("&Exporter"));
	fileMenu->addAction(exportAct1);
	fileMenu->addAction(exportAct2);
	fileMenu->addSeparator();
	QKeySequence racourci1(Qt::CTRL + Qt::Key_1);
	QKeySequence racourci2(Qt::CTRL + Qt::Key_2);
	exportAct1->setShortcut(racourci1);
	exportAct2->setShortcut(racourci2);

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
