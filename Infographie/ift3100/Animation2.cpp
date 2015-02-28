#include <Include\Macros.hpp>
#include <Include\Shader.hpp>
#include <Primitives\ShapeGenerator.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <qfiledialog.h>
#include "Animation2.h"


using glm::vec3;
using glm::vec4;
using glm::mat4;


/*-----------------------------------------------------------------------------
*  CODE DU SHADER
*-----------------------------------------------------------------------------*/

const char * vert2 = GLSL(
	
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

const char * frag2 = GLSL(
	
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

Shader * shader2;

// ID de Vertex Attribute
GLuint positionID2, colorID2;
// Buffer ID
GLuint bufferID2, elementID2;
// Array ID
GLuint arrayID2;
// ID Uniform
GLuint modelID2, viewID2, projectionID2;



void Animation2::initializeGL()
{
	OpenGL::initializeGL();

	installerShader();
	envoyerData();
}

void Animation2::installerShader()
{
	// Création du shader
	shader2 = new Shader(vert2, frag2);

	// attribut locations
	positionID2 = glGetAttribLocation(shader2->id(), "position");
	colorID2 = glGetAttribLocation(shader2->id(), "color");

	// uniform locations
	modelID2 = glGetUniformLocation(shader2->id(), "model");
	viewID2 = glGetUniformLocation(shader2->id(), "view");
	projectionID2 = glGetUniformLocation(shader2->id(), "projection");
}

void Animation2::envoyerData()
{
	ShapeData triangle = ShapeGenerator::makeTriangle();

	// vertex array object
	glGenVertexArrays(1, &arrayID2);
	glBindVertexArray(arrayID2);

	// vertex buffer object
	glGenBuffers(1, &bufferID2);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID2);
	glBufferData(GL_ARRAY_BUFFER, triangle.vertexBufferSize(), triangle.vertices, GL_STATIC_DRAW);

	// element array buffer object
	glGenBuffers(1, &elementID2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.indexBufferSize(), triangle.indices, GL_STATIC_DRAW);

	// vertex attributes
	glEnableVertexAttribArray(positionID2);
	glEnableVertexAttribArray(colorID2);
	glVertexAttribPointer(positionID2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::offsetColor());

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
	shader2->bind();
	glBindVertexArray(arrayID2);


	/*-----------------------------------------------------------------------------
	*  Matrices : View & Projection
	*-----------------------------------------------------------------------------*/

	vec3 eyepos = vec3(cos(time) * 1.0, 0, sin(time) * 5.0);

	//                      eye     target         up
	mat4 view = glm::lookAt(eyepos, vec3(0, 0, 0), vec3(0, 1, 0));

	mat4 projection = glm::perspective(PI / 3.0f, ((float)width()) / height(), 0.1f, 10.0f);
	
	glUniformMatrix4fv(viewID2, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionID2, 1, GL_FALSE, glm::value_ptr(projection));


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

				vec3 trs(-len / 2.0 + i, -len / 2.0 + j, -len / 2.0 + k);
				vec3 axis(0, 0, 1);
				float rad = time * PI;
				vec3 vscale(1.0 - (float)idx / total);

				mat4 translation = glm::translate(mat4(), trs);
				mat4 rotation = glm::rotate(mat4(), rad, axis);
				mat4 scale = glm::scale(mat4(), vscale);

				// Matrice du model
				mat4 model = translation * rotation * scale;

				glUniformMatrix4fv(modelID2, 1, GL_FALSE, glm::value_ptr(model));
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
			}
		}
	}

	// Mise à jour du framebuffer
	update();

	// unbind
	glBindVertexArray(0);
	shader2->unbind();
}

Animation2::~Animation2()
{
	glDeleteBuffers(1, &bufferID2);
	glDeleteBuffers(1, &elementID2);
	
	delete shader2;
}

void Animation2::enregistrerImage(){
	QImage imageFrame = grabFramebuffer();
	QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
	imageFrame.save(file, "JPEG");
}