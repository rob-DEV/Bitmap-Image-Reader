#pragma once
#include "../console/console.h"
#include <string>
#include <fstream>
#include <vector>

extern Console& console;

class BitmapImage
{
private:
	std::string m_FilePath;

private:
	void loadBitmap();

public:
	BitmapImage(const char* filePath);
	~BitmapImage();
};

struct Pixel
{
	unsigned char r, g, b = 0;
};

