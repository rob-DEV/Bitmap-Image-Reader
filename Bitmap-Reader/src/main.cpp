#include "console/console.h"
#include "bitmap/bitmap.h"

int _main()
{
	Console& console = Console::GetConsole();
	Bitmap bitmapTest("res/large_image_test.bmp");

	bitmapTest.invert();

	console.Pause();
	return 0;
}

int main()
{
	_main();
	return 0;
}