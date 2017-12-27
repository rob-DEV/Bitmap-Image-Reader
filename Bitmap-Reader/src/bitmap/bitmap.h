#pragma once
#include "../console/console.h"
#include <string>
#include <fstream>

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

