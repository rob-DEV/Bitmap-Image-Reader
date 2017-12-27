#include "console/console.h"
#include "bitmap/bitmap.h"

Console& console = Console::GetConsole();

int main()
{
	Bitmap bitmapTest("res/large_image_test.bmp");
	
	bitmapTest.invert();

	console.Pause();
}