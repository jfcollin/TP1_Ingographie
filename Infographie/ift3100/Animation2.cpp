#include <iostream>
#include "Animation2.h"
#include <qfiledialog.h>

Animation2::~Animation2()
{
}

void Animation2::initializeGL()
{
}

void Animation2::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
}

void Animation2::enregistrerImage(){
	QImage imageFrame = grabFramebuffer();
	QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
	imageFrame.save(file, "JPEG");
}