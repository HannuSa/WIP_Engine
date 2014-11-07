#include "Render.h"
#include "Debug.h"

Render::Render()
{
	InitializeShaders();
}

Render::~Render()
{
	glDeleteBuffers(2, buffers);
	glDeleteProgram(shaderProgram);
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
	vertexString = ResourceManager::TextFileRead("VertexShader.glsl");
	glShaderSource(vertexObject, 1, &vertexString, NULL);
	free(vertexString);
	glCompileShader(vertexObject);


	glGetShaderiv(vertexObject, GL_COMPILE_STATUS, &compile);
	Debug::KillMessage(compile == GL_TRUE,"vertexObject compile failed");


	//Fragment shader creation
	fragmentObject = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentString = ResourceManager::TextFileRead("FragmentShader.glsl");
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

	Debug::KillMessage(compile == GL_TRUE, "shaderProgram Link failed");
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

	uniSampler = glGetUniformLocation(shaderProgram, "uniSampler2D");
	assert(uniSampler >= 0);

	projectionLocation = glGetUniformLocation(shaderProgram, "unifProjection");
	assert(projectionLocation >= 0);
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

void Render::EnableBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::InitializeProjection()
{
	const glm::mat4 projection = glm::ortho(0.0f, 1200.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&projection));
	glUseProgram(0u);
}

void Render::BeginSpriteBatch()
{

}

void Render::DrawSprite(Sprite &_sprite)
{
		//spriteBatch.push_back(&_sprite);

	memoryHandler.Allocate(4 * 7, 6);
	glm::vec2 spritePos = _sprite.getPos();
	GLfloat spriteWidth = _sprite.getWidth();
	GLfloat spriteHeight = _sprite.getHeight();
	//1st vertex
	memoryHandler.setPos(0, spritePos.x, spritePos.y);
	memoryHandler.setTexture(0, 0.0f, 1.0f);
	//2nd vertex
	memoryHandler.setPos(1, spritePos.x + spriteWidth, spritePos.y);
	memoryHandler.setTexture(1, 1.0f, 1.0f);
	//3rd vertex
	memoryHandler.setPos(2, spritePos.x + spriteWidth, spritePos.y + spriteHeight);
	memoryHandler.setTexture(2, 1.0f, 0.0f);
	//4th vertex
	memoryHandler.setPos(3, spritePos.x, spritePos.y + spriteHeight);
	memoryHandler.setTexture(3, 0.0f, 0.0f);

}

void Render::EndSpriteBatch()
{
	for (int i = 0; i < spriteBatch.size(); i++)
	{
		
	}

	spriteBatch.clear();
}

void Render::DebugDrawStuff(Texture* _texture)
{
	glUseProgram(shaderProgram);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBindTexture(GL_TEXTURE_2D, _texture->texture);
	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, uniSamplerLoc);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}