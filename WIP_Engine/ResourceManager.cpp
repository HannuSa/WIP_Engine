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