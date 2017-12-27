#include "console/console.h"
#include "bitmap/bitmap.h"

Console& console = Console::GetConsole();

int main()
{
	BitmapImage bitmapTest("res/test.bmp");
	console.Pause();
}