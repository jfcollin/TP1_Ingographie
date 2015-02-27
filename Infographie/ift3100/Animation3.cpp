#include <Include\Macros.hpp>
#include <Include\Shader.hpp>
#include <Include\Data.hpp>
#include <Primitives\ShapeGenerator.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <qfiledialog.h>
#include "Animation3.h"


using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;


/*-----------------------------------------------------------------------------
*  CODE DU SHADER
*-----------------------------------------------------------------------------*/

const char * vert3 = GLSL(

	150,  // version de GLSL

	in vec3 position;
	in vec3 color;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	out vec3 vertexShaderColor;

	void main()
	{
		vec4 v = vec4(position, 1.0);
		gl_Position = projection * view * model * v;
		vertexShaderColor = color;
	}
);

const char * frag3 = GLSL(

	150,  // version de GLSL

	in vec3 vertexShaderColor;
	out vec4 fragmentShaderColor;

	void main()
	{
		fragmentShaderColor = vec4(vertexShaderColor, 1.0);
	}
);


/*-----------------------------------------------------------------------------
*  VARIABLES GLOBALES
*-----------------------------------------------------------------------------*/

Shader * shader3;

// ID de Vertex Attribute
GLuint positionID3, colorID3;
// Buffer ID
GLuint bufferID3, elementID3;
// Array ID
GLuint arrayID3;
// ID Uniform
GLuint modelID3, viewID3, projectionID3;



void Animation3::initializeGL()
{
	OpenGL::initializeGL();

	installerShader();
	envoyerData();
}

void Animation3::installerShader()
{
	// Cr�ation du shader
	shader3 = new Shader(vert3, frag3);

	// attribut locations
	positionID3 = glGetAttribLocation(shader3->id(), "position");
	colorID3 = glGetAttribLocation(shader3->id(), "color");

	// uniform locations
	modelID3 = glGetUniformLocation(shader3->id(), "model");
	viewID3 = glGetUniformLocation(shader3->id(), "view");
	projectionID3 = glGetUniformLocation(shader3->id(), "projection");
}

void Animation3::envoyerData()
{
	ShapeData cube = ShapeGenerator::makeCube();

	// vertex array object
	glGenVertexArrays(1, &arrayID3);
	glBindVertexArray(arrayID3);

	// vertex buffer object
	glGenBuffers(1, &bufferID3);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID3);
	glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.vertices, GL_STATIC_DRAW);

	// element array buffer object
	glGenBuffers(1, &elementID3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), cube.indices, GL_STATIC_DRAW);

	// vertex attributes
	glEnableVertexAttribArray(positionID3);
	glEnableVertexAttribArray(colorID3);
	glVertexAttribPointer(positionID3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(colorID3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) sizeof(vec3));

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	cube.destroy();
}

void Animation3::paintGL()
{
	glViewport(0, 0, width(), height());
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


	static float time = 0.0;
	time += .01;

	
	// Bind Shader, Vertex Array Object
	shader3->bind();
	glBindVertexArray(arrayID3);


	/*-----------------------------------------------------------------------------
	*  Matrices : Model, View, Projection
	*-----------------------------------------------------------------------------*/

	// transformations � appliquer au cube
	mat4 rotation = glm::rotate(mat4(), time, vec3(0, 1, 0));
	mat4 scale = glm::scale(mat4(), vec3(sin(time) * 2, 1, 1));

	// Model
	mat4 model = rotation * scale;
	glUniformMatrix4fv(modelID3, 1, GL_FALSE, glm::value_ptr(model));

	// View
	mat4 view = glm::lookAt(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));
	glUniformMatrix4fv(viewID3, 1, GL_FALSE, glm::value_ptr(view));

	// Projection
	mat4 proj = glm::perspective(PI / 3.0f, ((float)width()) / height(), 0.1f, 10.0f);
	glUniformMatrix4fv(projectionID3, 1, GL_FALSE, glm::value_ptr(proj));

	/*---------------------------------------------------------------------------*/


	// Dessin du cube
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);



	// Mise � jour du framebuffer
	update();

	// unbind
	glBindVertexArray(0);
	shader3->unbind();
}

Animation3::~Animation3()
{
	glDeleteBuffers(1, &bufferID3);
	glDeleteBuffers(1, &elementID3);

	delete shader3;
}

void Animation3::enregistrerImage(){
	QImage imageFrame = grabFramebuffer();
	QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
	imageFrame.save(file, "JPEG");
}