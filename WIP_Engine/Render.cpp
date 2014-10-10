#include "Render.h"
#include "Debug.h"

Render::Render()
{
	InitializeShaders();
}

Render::~Render()
{
}

void Render::InitializeShaders()
{
	GLuint glewOK;
	glewOK = glewInit();
	Debug::KillMessage(glewOK == GLEW_OK, "Glew initialization failed");

	char* vertexString;
	char *fragmentString;
	GLint compile;

	//Vertex shader creation
	vertexObject = glCreateShader(GL_VERTEX_SHADER);
	vertexString = res.TextFileRead("VertexShader.glsl");
	glShaderSource(vertexObject, 1, &vertexString, NULL);
	free(vertexString);
	glCompileShader(vertexObject);


	glGetShaderiv(vertexObject, GL_COMPILE_STATUS, &compile);
	Debug::KillMessage(compile == GL_TRUE,"vertexObject compile failed");


	//Fragment shader creation
	fragmentObject = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentString = res.TextFileRead("FragmentShader.glsl");
	glShaderSource(fragmentObject, 1, &fragmentString, NULL);
	free(fragmentString);
	glCompileShader(fragmentObject);

	glGetShaderiv(fragmentObject, GL_COMPILE_STATUS, &compile);
	Debug::KillMessage(compile == GL_TRUE, "fragmentObject compile failed");


	//Program creation and linking
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexObject);
	glAttachShader(shaderProgram, fragmentObject);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compile);

	Debug::KillMessage(compile == GL_TRUE, "shaderObject Link failed");
}

void Render::EnableAttributeArray()
{
	positionIndex = glGetAttribLocation(shaderProgram, "attrPosition");
	assert(positionIndex >= 0);
	glEnableVertexAttribArray(positionIndex);

	colorIndex = glGetAttribLocation(shaderProgram, "attrColor");
	assert(colorIndex >= 0);
	glEnableVertexAttribArray(colorIndex);

	texCoordIndex = glGetAttribLocation(shaderProgram, "attrTexCoords");
	assert(texCoordIndex >= 0);
	glEnableVertexAttribArray(texCoordIndex);
}

void Render::CreateBuffers(GLsizeiptr _vertexSize, GLsizeiptr _indexSize, const GLfloat* _vertexData, const GLuint* _indexData)
{
	glGenBuffers(2, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, _vertexSize, _vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexSize, _indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Render::EnableUniformSampler()
{
	uniSamplerLoc = glGetUniformLocation(shaderProgram, "uniSampler2D");
}

void Render::DebugDrawStuff(Texture _texture)
{
	glUseProgram(shaderProgram);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBindTexture(GL_TEXTURE_2D, _texture.texture);
	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, uniSamplerLoc);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}