#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <QMouseEvent>
#include <QKeyEvent>
#include <Primitives\Vertex.h>
#include <Primitives\ShapeGenerator.h>
#include <fstream>
#include <iostream>
#include "Animation1.h"
#include "Camera.h"
#include <qfiledialog.h>
using namespace std;
using glm::vec3;
using glm::mat4;


GLuint programID;
GLuint numIndices;
int mBackground = 1;

float mRotation = 0.0f;

int Compteur = 0;
bool blnZoom = true;
int Direction = 1;
Camera camera;

Animation1::~Animation1()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

void Animation1::initializeGL()
{
	// Initialisation de GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// glewInit ne fonctionne pas...
		fprintf(stderr, "Erreur: %s\n", glewGetErrorString(err));
	}

	glEnable(GL_DEPTH_TEST);

	sendDataToOpenGL();
	installShaders();
	
	//mise en place d'un timer de refresh
	QObject::connect(&mDrawTimer, SIGNAL(timeout()), this, SLOT(update()));
	mDrawTimer.start(500.0f);
}

void Animation1::paintGL()
{
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	mBackground *= -1;
	
	if (blnZoom)
	{
		if (Direction == 1)
		{

			camera.moveBackward();
			Compteur++;
		}
		else
		{
			camera.moveForward();
			Compteur++;
		}
	}
	else
	{
		if (Direction == 1)
		{

			camera.strafeLeft();
			Compteur++;
		}
		else
		{
			camera.strafeRight();
			Compteur++;
		}
	}
	
	
	
	//Dessin des cubes avec la rotation d'un des cubes
	mat4 projectionMatrix = glm::perspective(1.6f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 fullTransforms[] =
	{
		projectionMatrix * camera.getViewMatrix() * glm::translate(vec3(-1.0f, 0.0f, -3.0f)) * glm::rotate(0.69f + mRotation, vec3(1.0f, 0.0f, 0.0f)) * glm::scale(vec3(0.5f, 1.0f, 1.0f)),
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);
	
	mRotation += 0.1f;
	
	if (Compteur == 10 && blnZoom)
	{
		Direction *= -1;
	}
	else if (Compteur == 20 && blnZoom)
	{
		blnZoom = false;
		Direction *= -1;
		Compteur = 0;
	}
	else if (Compteur == 25 && !blnZoom)
	{
		Direction *= -1;
	}
	else if (Compteur == 50 && !blnZoom)
	{
		blnZoom = true;
		Direction *= -1;
		Compteur = 0;
	}
	
}

void Animation1::sendDataToOpenGL()
{
	ShapeData shape = ShapeGenerator::makeCube();
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLuint indexArrayBufferID;
	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	numIndices = shape.numIndices;
	shape.destroy();

	GLuint transformationMatrixBufferID;
	glGenBuffers(1, &transformationMatrixBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, transformationMatrixBufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * 2, 0, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 12));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
}

void Animation1::installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	//GLuint programID = glCreateProgram();
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glBindAttribLocation(programID, 0, "position");
	glBindAttribLocation(programID, 1, "vertexColor");
	glBindAttribLocation(programID, 2, "fullTransformMatrix");

	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
}

bool Animation1::checkShaderStatus(GLuint shaderID)
{
	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl << endl;
		delete[] buffer;

		return false;
	}
	return true;
}

bool Animation1::checkProgramStatus(GLuint programID)
{
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl << endl;
		delete[] buffer;
		
		return false;
	}
	return true;
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
	mDrawTimer.stop();
	QImage imageFrame = grabFramebuffer();
	QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
	imageFrame.save(file, "JPEG");
	mDrawTimer.start(500.0f);
}