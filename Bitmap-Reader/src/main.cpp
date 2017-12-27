#include "console/console.h"
#include "bitmap/bitmap.h"

Console& console = Console::GetConsole();

int main()
{
	BitmapImage bitmapTest("res/large_image_test.bmp");
	console.Pause();
}