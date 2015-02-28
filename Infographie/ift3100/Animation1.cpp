#include <GL\glew.h>

#include <Include\Camera.hpp>
#include <Include\Macros.hpp>
#include <Include\Shader.hpp>
#include <Primitives\ShapeGenerator.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include <QMouseEvent>
#include <QKeyEvent>

#include <fstream>
#include <iostream>
#include <qfiledialog.h>

#include "Animation1.h"


using namespace std;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;


/*-----------------------------------------------------------------------------
*  CODE DU SHADER
*-----------------------------------------------------------------------------*/

const char * vert = GLSL(

	150,  // version de GLSL

	in vec3 position;
	in vec4 color;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	out vec4 vertexShaderColor;

	void main()
	{
		vec4 v = vec4(position, 1.0);
		gl_Position = projection * view * model * v;
		vertexShaderColor = color;
	}
);

const char * frag = GLSL(

	150,  // version de GLSL

	in vec4 vertexShaderColor;

	void main()
	{
		gl_FragColor = vertexShaderColor;
	}
);


/*-----------------------------------------------------------------------------
*  VARIABLES GLOBALES
*-----------------------------------------------------------------------------*/

Shader * shader;
Camera camera;

// ID de Vertex Attribute
GLuint positionID, colorID;
// Buffer ID
GLuint bufferID, elementID;
// Array ID
GLuint cubeArrayID, pyramidArrayID;
// ID Uniform
GLuint modelID, viewID, projectionID;

// Nombre d'indices
GLuint cubeNumIndices, pyramidNumIndices;


void Animation1::initializeGL()
{
	OpenGL::initializeGL();
	
	installerShader();
	envoyerData();
}

void Animation1::installerShader()
{
	// Création du shader
	shader = new Shader(vert, frag);

	// attribut locations
	positionID = glGetAttribLocation(shader->id(), "position");
	colorID = glGetAttribLocation(shader->id(), "color");

	// uniform locations
	modelID = glGetUniformLocation(shader->id(), "model");
	viewID = glGetUniformLocation(shader->id(), "view");
	projectionID = glGetUniformLocation(shader->id(), "projection");
}

void Animation1::envoyerData()
{

	/*-----------------------------------------------------------------------------
	*  Cube
	*-----------------------------------------------------------------------------*/

	ShapeData cube = ShapeGenerator::makeCube();
		
	// vertex array object
	glGenVertexArrays(1, &cubeArrayID);
	glBindVertexArray(cubeArrayID);

	// vertex buffer object
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.vertices, GL_STATIC_DRAW);

	// element array buffer object
	glGenBuffers(1, &elementID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), cube.indices, GL_STATIC_DRAW);

	// vertex attributes
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::offsetColor());

	cubeNumIndices = cube.numIndices;

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	cube.destroy();


	/*-----------------------------------------------------------------------------
	*  Pyramide
	*-----------------------------------------------------------------------------*/

	ShapeData pyramide = ShapeGenerator::makePyramid();

	// vertex array object
	glGenVertexArrays(1, &pyramidArrayID);
	glBindVertexArray(pyramidArrayID);

	// vertex buffer object
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, pyramide.vertexBufferSize(), pyramide.vertices, GL_STATIC_DRAW);

	// element array buffer object
	glGenBuffers(1, &elementID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pyramide.indexBufferSize(), pyramide.indices, GL_STATIC_DRAW);

	// vertex attributes
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::offsetColor());

	pyramidNumIndices = pyramide.numIndices;

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	pyramide.destroy();

}

void Animation1::paintGL()
{
	OpenGL::paintGL();

	
	static float time = 0.0;
	time += .01;


	// Bind Shader
	shader->bind();


	/*-----------------------------------------------------------------------------
	*  Matrices : View & Projection
	*-----------------------------------------------------------------------------*/

	// View : avec la classe Camera
	mat4 view = camera.getViewMatrix();
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));

	// Projection
	mat4 proj = glm::perspective(1.0f, ((float)width()) / height(), 0.1f, 20.0f);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));


	/*-----------------------------------------------------------------------------
	*  Cube
	*-----------------------------------------------------------------------------*/

	glBindVertexArray(cubeArrayID);

	// transformations à appliquer au cube
	mat4 cubeTranslation = glm::translate(vec3(-1.5f, 0.0f, -6.0f));
	mat4 cubeRotation = glm::rotate(time, vec3(0.0f, 1.0f, 0.0f)) *
					    glm::rotate(-0.5f, vec3(1.0f, 0.0f, 0.0f));
	mat4 cubeScale = glm::scale(vec3(sin(time) * 2, 1, 1));

	// Model
	mat4 cubeModel = cubeTranslation * cubeRotation * cubeScale;
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(cubeModel));

	// Dessin du cube
	glDrawElements(GL_QUADS, cubeNumIndices, GL_UNSIGNED_SHORT, 0);


	/*-----------------------------------------------------------------------------
	*  Pyramide
	*-----------------------------------------------------------------------------*/

	glBindVertexArray(pyramidArrayID);

	// transformations à appliquer au cube
	mat4 pyramidTranslation = glm::translate(vec3(1.5f, 0.0f, -5.0f));
	mat4 pyramidRotation = glm::rotate(-time, vec3(0.0f, 1.0f, 0.0f)) *
		                   glm::rotate(-0.2f, vec3(1.0f, 0.0f, 0.0f));

	// Model
	mat4 pyramidModel = pyramidTranslation * pyramidRotation;
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(pyramidModel));

	// Dessin du cube
	glDrawElements(GL_TRIANGLES, pyramidNumIndices, GL_UNSIGNED_SHORT, 0);

	update();

	// unbind
	glBindVertexArray(0);
	shader->unbind();
}

Animation1::~Animation1()
{
	glDeleteBuffers(1, &bufferID);
	glDeleteBuffers(1, &elementID);

	delete shader;
}

void Animation1::mouseMoveEvent(QMouseEvent* e)
{
	camera.mouseUpdate(vec2(e->x(), e->y()));

	update();
}

void Animation1::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		camera.moveForward();
		break;
	case Qt::Key::Key_S:
		camera.moveBackward();
		break;
	case Qt::Key::Key_A:
		camera.moveLeft();
		break;
	case Qt::Key::Key_D:
		camera.moveRight();
		break;
	case Qt::Key::Key_R:
		camera.moveUp();
		break;
	case Qt::Key::Key_F:
		camera.moveDown();
		break;
	}

	update();
}

string Animation1::readShaderCode(const char* fileName)
{
	ifstream input(fileName);
	if (!input.good())
	{
		cout << "Impossible de charger le fichier..." << endl << endl;
		exit(1);
	}

	string fileRead = string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());
	input.close();

	return fileRead;
}

void Animation1::enregistrerImage(){
	QImage imageFrame = grabFramebuffer();
	QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
	imageFrame.save(file, "JPEG");
}