#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL\glew.h>
#include <iostream>

class Shader
{
	GLuint programID;

public:

	Shader(const char* vert, const char* frag) {

	/*-----------------------------------------------------------------------------
	*  Créer les shaders de sommets et de fragments
	*----------------------------------------------------------------------------*/

		// 1. Création du programme
		programID = glCreateProgram();
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// 2. Charger les codes sources des shaders
		glShaderSource(vertexShaderID, 1, &vert, 0);
		glShaderSource(fragmentShaderID, 1, &frag, 0);

		// 3. Compiler
		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		// 4. Vérifier les erreurs de compilation
		compilerCheck(vertexShaderID);
		compilerCheck(fragmentShaderID);

		// 5. Attacher les shaders au programme
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

		// 6. Link du programme
		glLinkProgram(programID);

		// 7. Vérifier les erreurs de lien
		linkCheck(programID);

		// 8. Supprimer les shaders
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		// 9. Utiliser le programme
		glUseProgram(programID);
	}

	/*-----------------------------------------------------------------------------
	*  Fonctions utilitaires
	*----------------------------------------------------------------------------*/
	GLuint id() const { return programID; }
	void bind() { glUseProgram(programID); }
	void unbind() { glUseProgram(0); }

	/*-----------------------------------------------------------------------------
	*  Vérification des erreurs à la compilation du shader
	*----------------------------------------------------------------------------*/
	void compilerCheck(GLuint shaderID)
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
			std::cout << buffer << std::endl;
			delete[] buffer;
		}
	}
	
	/*-----------------------------------------------------------------------------
	*  Vérification des erreurs de lien au programme
	*----------------------------------------------------------------------------*/
	void linkCheck(GLuint programID)
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
			std::cout << buffer << std::endl;
			delete[] buffer;
		}
	}
};

#endif // !SHADER_HPP


