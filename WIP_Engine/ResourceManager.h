#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <iostream>
#include "lodepng.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void LoadPixelData(std::string _filename);
private:
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //raw pixels

};
#endif