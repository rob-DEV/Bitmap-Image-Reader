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
	int length = (int)stream.tellg();
	stream.seekg(0, stream.beg);

	unsigned short bmp_signature = 0;
	unsigned int bmp_file_size = 0;
	unsigned short bmp_reserved_1 = 0;
	unsigned short bmp_reserved_2 = 0;
	unsigned int bmp_pixel_offset = 0;
	unsigned int bmp_dib_header_size = 0;
	unsigned int bmp_width = 0;
	unsigned int bmp_height = 0;
	unsigned short bmp_image_planes = 0;
	unsigned short bmp_image_bits_per_pixel = 0;
	unsigned int bmp_image_compression = 0;
	unsigned int bmp_image_size = 0;
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
	stream.read(reinterpret_cast<char*>(&bmp_dib_header_size), 4);
	//read the image width
	stream.read(reinterpret_cast<char*>(&bmp_width), 4);
	//read the image height
	stream.read(reinterpret_cast<char*>(&bmp_height), 4);
	//read image planes
	stream.read(reinterpret_cast<char*>(&bmp_image_planes), 2);
	//read bits per pixel should be 24 hence rgb, 8 bits (1 byte) each
	stream.read(reinterpret_cast<char*>(&bmp_image_bits_per_pixel), 2);
	//read image compression
	stream.read(reinterpret_cast<char*>(&bmp_image_compression), 4);
	//read image size
	stream.read(reinterpret_cast<char*>(&bmp_image_size), 4);

	std::cout << "BMP type: " << bmp_signature << std::endl;
	std::cout << "BMP file size: " << bmp_file_size << std::endl;
	std::cout << "BMP reserved 1: " << bmp_reserved_1 << std::endl;
	std::cout << "BMP reserved 2: " << bmp_reserved_2 << std::endl;
	std::cout << "BMP pixel offset: " << bmp_pixel_offset << std::endl;
	std::cout << "BMP DIB header size: " << bmp_dib_header_size << std::endl;
	std::cout << "BMP image width: " << bmp_width << std::endl;
	std::cout << "BMP image height: " << bmp_height << std::endl;
	std::cout << "BMP image planes: " << bmp_image_planes << std::endl;
	std::cout << "BMP image bits per pixel: " << bmp_image_bits_per_pixel << std::endl;
	std::cout << "BMP image compression: " << bmp_image_compression << std::endl;
	std::cout << "BMP image size: " << bmp_image_size << std::endl;

	//seek to the pixel array from the beginning to the offset
	stream.seekg(bmp_pixel_offset, stream.beg);
	
	std::vector<Pixel> pixels;
	//size - actual pixel size = padding
	for (size_t i = 0; i < bmp_height * bmp_width; i++)
	{
		//stream reads in pixels in the format bgr instead of rgb
		//the structure of the pixel structure figures this out correctly
		Pixel pixel;
		stream.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
		pixels.push_back(pixel);



		//std::cout << "At: " << streamPos << " r: " << (unsigned int)pixel.r << " g: " << (unsigned int)pixel.g << " b:" << (unsigned int)pixel.b << std::endl;
	}

	stream.close();


	std::cout << "Begin Colour Invert!" << std::endl;

	std::ofstream writeStream;
	writeStream.open(m_FilePath.c_str(), std::ios::binary | std::ios::in);
	
	if (!writeStream)
	{
		console.Log("loadBitmap() : File Not Found!");
		return;
	}

	//invert colours of each pixels and overwrite image
	for (size_t i = 0; i < pixels.size(); i++)
		pixels[i].invert();

	/*
	writeStream.seekp(0, writeStream.end);
	int lengthy = writeStream.tellp();
	writeStream.seekp(0, writeStream.beg);
	std::cout << lengthy;
	*/
	writeStream.clear();
	writeStream.seekp(bmp_pixel_offset, std::ios::beg);

	for (size_t i = 0; i < bmp_height * bmp_width; i++)
		writeStream.write(reinterpret_cast<char*>(&pixels[i]), 3);

	std::cout << "Invertion Complete!" << std::endl;

}
