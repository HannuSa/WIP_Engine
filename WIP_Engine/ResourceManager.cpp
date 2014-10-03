#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}


void ResourceManager::LoadPixelData(std::string _filename)
{
	unsigned width, height;
	lodepng::load_file(png, _filename);
	unsigned error = lodepng::decode(image, width, height, png);

	if (error)
		std::cout << "decoder error" << error <<":" << lodepng_error_text(error) << std::endl;

	//the pixels are now int the vector "image", 4 bytes per pixel, ordered RGBARGBA...
}