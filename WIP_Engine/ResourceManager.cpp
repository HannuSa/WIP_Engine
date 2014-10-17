#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	glDeleteTextures(1, 0);
}

Texture* ResourceManager::CheckTextureID(int _id)
{
	std::map<int, Texture>::iterator it;

	it = textures.find(_id);

	if (it != textures.end())
		return &(it->second);
	else
		return NULL;
}

Texture ResourceManager::LoadTextureFromFile(std::string _filename)
{
	int id = hasher(_filename);

	std::vector<unsigned char> tempData;
	unsigned int tempWidth, tempHeight;

	if (CheckTextureID(id) == NULL)
	{
		unsigned int error = lodepng::decode(tempData, tempWidth, tempHeight, _filename);
		Debug::KillMessage(error == 0, "Failed to load image");

		Texture tempTex(tempData, tempWidth, tempHeight, id);

		AddTexture(id, tempTex);

		return tempTex;
	}
	else
		return *CheckTextureID(id);
}	

void ResourceManager::AddTexture(int _id, Texture _texture)
{
	textures.insert(std::make_pair(_id, _texture));
}

char* ResourceManager::TextFileRead(char* _filename)
{
	FILE *fp;
	char *content = NULL;
	int count = 0;

	if (_filename != NULL)
	{
		fp = fopen(_filename, "rb");

		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count + 1));
				fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}