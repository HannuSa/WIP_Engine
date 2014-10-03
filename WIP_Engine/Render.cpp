#include "Render.h"


Render::Render()
{
}


Render::~Render()
{
}

GLuint Render::SetShaders()
{
	char* vertexString;
	char *fragmentString;
	GLint compile;

	//Vertex shader creation
	vertexObject = glCreateShader(GL_VERTEX_SHADER);
	vertexString = textFileRead("VertexShader.hlsl");
	glShaderSource(vertexObject, 1, &vertexString, NULL);
	free(vertexString);
	glCompileShader(vertexObject);


	glGetShaderiv(vertexObject, GL_COMPILE_STATUS, &compile);
	assert(compile == GL_TRUE);


	//Fragment shader creation
	fragmentObject = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentString = textFileRead("FragmentShader.hlsl");
	glShaderSource(fragmentObject, 1, &fragmentString, NULL);
	free(fragmentString);
	glCompileShader(fragmentObject);

	glGetShaderiv(fragmentObject, GL_COMPILE_STATUS, &compile);
	assert(compile == GL_TRUE);


	//Program creation and linking
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexObject);
	glAttachShader(shaderProgram, fragmentObject);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compile);
	assert(compile == GL_TRUE);

	return shaderProgram;
}
