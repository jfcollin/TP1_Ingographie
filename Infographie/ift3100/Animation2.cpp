#include <Include\Macros.hpp>
#include <Include\Shader.hpp>
#include <Primitives\ShapeGenerator.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <qfiledialog.h>
#include "Animation2.h"


/*-----------------------------------------------------------------------------
*  CODE DU SHADER
*-----------------------------------------------------------------------------*/

const char * vert = GLSL(
	
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

const char * frag = GLSL(
	
	150,  // version de GLSL

	in vec3 vertexShaderColor;

	void main()
	{
		gl_FragColor = vec4(vertexShaderColor, 1.0);
	}
);


/*-----------------------------------------------------------------------------
*  VARIABLES GLOBALES
*-----------------------------------------------------------------------------*/

Shader * shader;

// ID de Vertex Attribute
GLuint positionID, colorID;
// Buffer ID
GLuint bufferID, elementID;
// Array ID
GLuint arrayID;
// ID Uniform
GLuint modelID, viewID, projectionID;



void Animation2::initializeGL()
{
	OpenGL::initializeGL();

	installerShader();
	envoyerData();
}

void Animation2::installerShader()
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

void Animation2::envoyerData()
{
	ShapeData triangle = ShapeGenerator::makeTriangle();

	// vertex array object
	glGenVertexArrays(1, &arrayID);
	glBindVertexArray(arrayID);

	// vertex buffer object
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, triangle.vertexBufferSize(), triangle.vertices, GL_STATIC_DRAW);

	// element array buffer object
	glGenBuffers(1, &elementID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.indexBufferSize(), triangle.indices, GL_STATIC_DRAW);

	// vertex attributes
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(glm::vec3));

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	triangle.destroy();
}

void Animation2::paintGL()
{
	OpenGL::paintGL();


	static float time = 0.0;
	time += .01;


	// Bind Shader, Vertex Array Object
	glUseProgram(shader->id());
	glBindVertexArray(arrayID);


	/*-----------------------------------------------------------------------------
	*  Matrices de View et de Projection
	*-----------------------------------------------------------------------------*/

	glm::vec3 eyepos = glm::vec3(cos(time) * 1.0, 0, sin(time)*5.0);

	//                            eye         target             up
	glm::mat4 view = glm::lookAt(eyepos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 projection = glm::perspective(PI / 3.0f, ((float)width()) / height(), 0.1f, 10.0f);
	
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));


	/*-----------------------------------------------------------------------------
	*  On dessine un paquet de triangles
	*-----------------------------------------------------------------------------*/
	
	int len = 10; 
	int total = len*len*len;

	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			for (int k = 0; k < len; ++k)
			{
				int idx = i * len * len + j * len + k;

				glm::vec3 trs(-len / 2.0 + i, -len / 2.0 + j, -len / 2.0 + k);
				glm::vec3 axis(0, 0, 1);
				float rad = time * PI;
				glm::vec3 vscale(1.0 - (float)idx / total);

				glm::mat4 translation = glm::translate(glm::mat4(), trs);
				glm::mat4 rotation = glm::rotate(glm::mat4(), rad, axis);
				glm::mat4 scale = glm::scale(glm::mat4(), vscale);

				glm::mat4 model = translation * rotation * scale;

				glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

				update();
			}
		}
	}
}

Animation2::~Animation2()
{
}

void Animation2::enregistrerImage(){
	QImage imageFrame = grabFramebuffer();
	QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
	imageFrame.save(file, "JPEG");
}