#include "bitmap.h"



BitmapImage::BitmapImage(const char* filePath)
{
	m_FilePath = std::string(filePath);
	loadBitmap();
}


BitmapImage::~BitmapImage()
{
}

void BitmapImage::loadBitmap()
{
	std::ifstream stream(m_FilePath.c_str(), std::ios::binary);
	if (!stream)
	{
		console.Log("loadBitmap() : File Not Found!");
		return;
	}

	//test: reading the header info byte by byte (24 bit bitmap file)
	stream.seekg(0, stream.end);
	int length = stream.tellg();
	stream.seekg(0, stream.beg);

	unsigned short bmp_signature = 0;
	unsigned int bmp_file_size = 0;
	unsigned short bmp_reserved_1 = 0;
	unsigned short bmp_reserved_2 = 0;
	unsigned int bmp_pixel_offset = 0;
	unsigned int bmp_dib_header_size = 0;
	unsigned int bmp_image_width = 0;
	unsigned int bmp_image_height = 0;

	//read in bmp modelled on the 24bit file format

	//read signature (bmp type) into short should be 19778
	stream.read(reinterpret_cast<char*>(&bmp_signature), 2);
	//read the file size into a 4 byte unsigned int
	stream.read(reinterpret_cast<char*>(&bmp_file_size), 4);
	//read past the 2 2 byte reserved chunks
	stream.read(reinterpret_cast<char*>(&bmp_reserved_1), 2);
	stream.read(reinterpret_cast<char*>(&bmp_reserved_2), 2);
	//read the pixel offset
	stream.read(reinterpret_cast<char*>(&bmp_pixel_offset), 4);
	//read the DIB header size
	stream.read(reinterpret_cast<char*>(&bmp_pixel_offset), 4);


	std::cout << "BMP type: " << bmp_signature << std::endl;
	std::cout << "BMP file size: " << bmp_file_size << std::endl;
	std::cout << "BMP reserved 1: " << bmp_reserved_1 << std::endl;
	std::cout << "BMP reserved 1: " << bmp_reserved_2 << std::endl;
	std::cout << "BMP pixel offset: " << bmp_pixel_offset << std::endl;
	std::cout << "BMP image width: " << bmp_image_width << std::endl;
	std::cout << "BMP image height: " << bmp_image_height << std::endl;
	//pixel offset is 54 bytes so seek to that point and then read to end



}
