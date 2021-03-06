#include "Render.h"
#include "Debug.h"

Render::Render(float _winWidth, float _winHeight)
{
	InitializeShaders();
	
	winWidth = _winWidth;
	winHeight = _winHeight;

	memoryHandler.Allocate(4 * 7, 6);
	buffers[0] = 0;
	buffers[1] = 0;
	
	EnableAttributeArray();
	EnableBlending();
	InitializeProjection();
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

	rotationIndex = glGetUniformLocation(shaderProgram, "rotMatrix");
	assert(rotationIndex >= 0);

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
	const glm::mat4 projection = glm::ortho(0.0f, winWidth, winHeight, 0.0f, -1.0f, 1.0f);

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&projection));
	glUseProgram(0u); 
}


void Render::DrawSprite(Sprite &_sprite)
{
	glm::vec2 spritePos = _sprite.GetPos(); 
	GLfloat spriteWidth = _sprite.GetWidth();
	GLfloat spriteHeight = _sprite.GetHeight();
	GLfloat spriteRectWidth = _sprite.GetRectWidth();
	GLfloat spriteRectHeight = _sprite.GetRectHeight();

	//1st vertex
	memoryHandler.setPos(0, spritePos.x, spritePos.y);
	
	//2nd vertex
	memoryHandler.setPos(1, spritePos.x + spriteWidth, spritePos.y);
	
	//3rd vertex
	memoryHandler.setPos(2, spritePos.x + spriteWidth, spritePos.y + spriteHeight);
	
	//4th vertex
	memoryHandler.setPos(3, spritePos.x, spritePos.y + spriteHeight);
	
	if (_sprite.hasRectangle == false)
	{
		memoryHandler.setTexture(0, 0.0f, 1.0f);
		memoryHandler.setTexture(1, 1.0f, 1.0f);
		memoryHandler.setTexture(2, 1.0f, 0.0f);
		memoryHandler.setTexture(3, 0.0f, 0.0f);
	}

	if (_sprite.hasRectangle == true)
	{
		memoryHandler.setTexture(0, _sprite.textureRectPos1.x, _sprite.textureRectPos1.y);
		memoryHandler.setTexture(1, _sprite.textureRectPos2.x , _sprite.textureRectPos2.y);
		memoryHandler.setTexture(2, _sprite.textureRectPos3.x, _sprite.textureRectPos3.y);
		memoryHandler.setTexture(3, _sprite.textureRectPos4.x, _sprite.textureRectPos4.y);
	}
	memoryHandler.setIndex(6, 0, 1, 2, 2, 3, 0);

	if (buffers[0] != 0)
	{
		glDeleteBuffers(2, buffers);
	}

	CreateBuffers(memoryHandler.getVertexSize(), memoryHandler.getIndexSize(), memoryHandler.vertexArray, memoryHandler.indexArray);

	glUseProgram(shaderProgram);


	glm::mat4 currMat(1.0f);
	currMat *= glm::translate(glm::vec3(_sprite.GetX()+0.5*_sprite.GetWidth(), _sprite.GetY()+0.5*_sprite.GetHeight(), 0.0f));
	currMat *= glm::rotate(_sprite.GetRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
	currMat *= glm::translate(glm::vec3(-(_sprite.GetX() + 0.5*_sprite.GetWidth()), -(_sprite.GetY() + 0.5*_sprite.GetHeight()), 0.0f));
	

	glUniformMatrix4fv(rotationIndex, 1, GL_FALSE, reinterpret_cast<const float*>(&currMat));

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBindTexture(GL_TEXTURE_2D, _sprite.GetTexture()->texture);
	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, uniSamplerLoc);
	glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}
