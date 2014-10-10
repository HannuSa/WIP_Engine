#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <iostream>
#include <map>
#include <functional>
#include "Texture.h"
#include "Debug.h"

class ResourceManager
{
public:
	static ResourceManager* Create()
	{
		if (instance == nullptr)
			instance = new ResourceManager();
		return instance;
	}

	Texture LoadTextureFromFile(std::string _filename);

	static char* TextFileRead(char* _filename);

	Texture* CheckTextureID(const int _id);
	void AddTexture(const int _id, Texture _texture);
private:
	ResourceManager();
	~ResourceManager();

	std::map<int, Texture> textures;
	std::hash<std::string> hasher;
	static ResourceManager* instance;
};
#endif