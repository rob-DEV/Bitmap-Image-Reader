#include "bitmap.h"

Bitmap::Bitmap(const char* filePath)
{
	m_FilePath = std::string(filePath);
	load();
}

Bitmap::~Bitmap()
{
	m_Image.clear();
}

void Bitmap::load()
{
	std::ifstream stream(m_FilePath.c_str(), std::ios::binary);
	if (!stream)
	{
		std::cout << "Bitmap::load() : File Not Found!" << std::endl;
		return;
	}

	read_from_stream(stream, m_Type);
	read_from_stream(stream, m_FileSize);
	read_from_stream(stream, m_Reserved_1);
	read_from_stream(stream, m_Reserved_2);
	read_from_stream(stream, m_PixelDataOffset);
	read_from_stream(stream, m_DibHeaderSize);
	read_from_stream(stream, m_Width);
	read_from_stream(stream, m_Height);
	read_from_stream(stream, m_Planes);
	read_from_stream(stream, m_BitsPerPixel);
	read_from_stream(stream, m_Compression);
	read_from_stream(stream, m_Image_Size);

	std::cout << "BMP type: " << m_Type << std::endl;
	std::cout << "BMP file size: " << m_FileSize << std::endl;
	std::cout << "BMP reserved 1: " << m_Reserved_1 << std::endl;
	std::cout << "BMP reserved 2: " << m_Reserved_2 << std::endl;
	std::cout << "BMP pixel offset: " << m_PixelDataOffset << std::endl;
	std::cout << "BMP DIB header size: " << m_DibHeaderSize << std::endl;
	std::cout << "BMP image width: " << m_Width << std::endl;
	std::cout << "BMP image height: " << m_Height << std::endl;
	std::cout << "BMP image planes: " << m_Planes << std::endl;
	std::cout << "BMP image bits per pixel: " << m_BitsPerPixel << std::endl;
	std::cout << "BMP image compression: " << m_Compression << std::endl;
	std::cout << "BMP image size: " << m_Image_Size << std::endl;
	
	//read the image data
	//seek to the pixel array from the beginning to the offset
	stream.seekg(m_PixelDataOffset, stream.beg);

	for (size_t i = 0; i < m_Width * m_Height; i++)
	{
		//stream reads in pixels in the format bgr instead of rgb
		//the structure of the pixel struct figures this out correctly
		Pixel pixel;
		read_from_stream(stream, pixel);
		m_Image.push_back(pixel);
	}

	stream.close();
}

void Bitmap::invert()
{
	std::cout << "Begin Colour Invert!" << std::endl;

	std::ofstream stream;
	stream.open(m_FilePath.c_str(), std::ios::binary | std::ios::in);

	if (!stream)
	{
		std::cout << "Bitmap::invert() : File Not Found!" << std::endl;
		return;
	}

	//invert colours of each pixels and overwrite image
	for (size_t i = 0; i < m_Image.size(); i++)
		m_Image[i].invert();

	stream.clear();
	stream.seekp(m_PixelDataOffset, std::ios::beg);

	for (size_t i = 0; i < m_Width * m_Height; i++)
		write_to_stream(stream, m_Image[i]);

	std::cout << "Invertion Complete!" << std::endl;
}

template<typename T>
void Bitmap::read_from_stream(std::ifstream& stream, T& t)
{
	stream.read(reinterpret_cast<char*>(&t), sizeof(T));
}

template<typename T>
void Bitmap::write_to_stream(std::ofstream& stream, T& t)
{
	stream.write(reinterpret_cast<char*>(&t), sizeof(T));
}
