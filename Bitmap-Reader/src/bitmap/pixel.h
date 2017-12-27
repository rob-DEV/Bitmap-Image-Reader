#pragma once

struct Pixel
{
	unsigned char b, g, r = 0;

	void invert()
	{
		b = 255 - b;
		g = 255 - g;
		r = 255 - r;
	}
};