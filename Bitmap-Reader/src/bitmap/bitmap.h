#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"

class Bitmap
{
private:
	std::string m_FilePath;
	unsigned short m_Type;
	unsigned int m_FileSize = 0;
	unsigned short m_Reserved_1 = 0;
	unsigned short m_Reserved_2 = 0;
	unsigned int m_PixelDataOffset = 0;
	unsigned int m_DibHeaderSize = 0;
	unsigned int m_Width = 0;
	unsigned int m_Height = 0;
	unsigned short m_Planes = 0;
	unsigned short m_BitsPerPixel = 0;
	unsigned int m_Compression = 0;
	unsigned int m_Image_Size = 0;

	std::vector<Pixel> m_Image;

private:
	void load();

	template<typename T>
	void read_from_stream(std::ifstream& stream, T& t);
	template<typename T>
	void write_to_stream(std::ofstream& stream, T& t);
public:
	Bitmap(const char* filePath);
	~Bitmap();
	void invert();
	
};

