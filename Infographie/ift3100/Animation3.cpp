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
using glm::mat3;
using glm::mat4;


/*-----------------------------------------------------------------------------
*  CODE DU SHADER
*-----------------------------------------------------------------------------*/

const char * vert3 = GLSL(

	150,  // version de GLSL

	in vec3 position;
	in vec3 normal;
	in vec2 textureCoordinate;
	in vec4 color;

	uniform mat4 projection;
	uniform mat4 view;
	uniform mat4 model;
	uniform mat3 normalMatrix;

	out vec2 texCoord;
	out float diffuse;

	// fonction pour calculer l'éclairage
	float eclairage()
	{
		vec3 norm = normalize(normalMatrix * normalize(normal));
		vec3 light = normalize(vec3(1.0, 1.0, 1.0));
		diffuse = max(dot(norm, light), 0.0);

		return diffuse;
	}

	void main(void)
	{
		diffuse = eclairage();
		texCoord = textureCoordinate;
		vec4 v = vec4(position, 1.0);
		gl_Position = projection * view * model * v;
	}
);

const char * frag3 = GLSL(

	150,  // version de GLSL

	uniform sampler2D sampler;

	in vec2 texCoord;
	in float diffuse;

	void main(void)
	{
		gl_FragColor = vec4(texture2D(sampler, texCoord).rgb * diffuse, 1.0);
	}
);


/*-----------------------------------------------------------------------------
*  VARIABLES GLOBALES
*-----------------------------------------------------------------------------*/

Shader * shader3;

// ID de Vertex Attribute
GLuint positionID3, normalID3, colorID3, textureCoordinateID3;
// Buffer ID
GLuint bufferID3, elementID3;
// Array ID
GLuint arrayID3;
// ID Uniform
GLuint modelID3, viewID3, projectionID3, normalMatrixID3;
// Texture ID
GLuint texID3;

/*-----------------------------------------------------------------------------
*  Chargement d'une image
*-----------------------------------------------------------------------------*/

Bitmap image("Resources/texture_metal.bmp");

int texWidth = image.width;
int texHeight = image.height;




void Animation3::initializeGL()
{
	OpenGL::initializeGL();

	installerShader();
	envoyerData();
}

void Animation3::installerShader()
{
	// Création du shader
	shader3 = new Shader(vert3, frag3);

	// attribut locations
	positionID3 = glGetAttribLocation(shader3->id(), "position");
	normalID3 = glGetAttribLocation(shader3->id(), "normal");
	textureCoordinateID3 = glGetAttribLocation(shader3->id(), "textureCoordinate");
	colorID3 = glGetAttribLocation(shader3->id(), "color");

	// uniform locations
	modelID3 = glGetUniformLocation(shader3->id(), "model");
	viewID3 = glGetUniformLocation(shader3->id(), "view");
	projectionID3 = glGetUniformLocation(shader3->id(), "projection");
	normalMatrixID3 = glGetUniformLocation(shader3->id(), "normalMatrix");
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
	glEnableVertexAttribArray(normalID3);
	glEnableVertexAttribArray(textureCoordinateID3);
	glEnableVertexAttribArray(colorID3);
	glVertexAttribPointer(positionID3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(normalID3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::offsetNormal());
	glVertexAttribPointer(textureCoordinateID3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::offsetTextureCoordinate());
	glVertexAttribPointer(colorID3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::offsetColor());

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	cube.destroy();


	/*-----------------------------------------------------------------------------
	*  TEXTURE
	*-----------------------------------------------------------------------------*/
	
	glGenTextures(1, &texID3);
	glBindTexture(GL_TEXTURE_2D, texID3);

	// Allocation de mémoire sur le GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Envoyer au GPU
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texWidth, texHeight, GL_BGR, GL_UNSIGNED_BYTE, image.pixels.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Animation3::paintGL()
{
	glViewport(0, 0, width(), height());
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


	static float time = 0.0;
	time += .01;

	
	// Bind Shader, Vertex Array Object
	shader3->bind();
	glBindTexture(GL_TEXTURE_2D, texID3);
	glBindVertexArray(arrayID3);


	/*-----------------------------------------------------------------------------
	*  Matrices : Model, View, Projection
	*-----------------------------------------------------------------------------*/

	// Model
	mat4 model = glm::rotate(mat4(), time, vec3(0, 1, 0));
	glUniformMatrix4fv(modelID3, 1, GL_FALSE, glm::value_ptr(model));

	// View
	mat4 view = glm::lookAt(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));
	glUniformMatrix4fv(viewID3, 1, GL_FALSE, glm::value_ptr(view));

	// Projection
	mat4 proj = glm::perspective(PI / 3.0f, ((float)width()) / height(), 0.1f, 20.0f);
	glUniformMatrix4fv(projectionID3, 1, GL_FALSE, glm::value_ptr(proj));

	// Normalization
	mat3 normalMatrix = glm::transpose(glm::inverse(mat3(view * model)));
	glUniformMatrix3fv(normalID3, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	/*---------------------------------------------------------------------------*/


	// Dessin du cube
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);



	// Mise à jour du framebuffer
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