#pragma once
#include <objidl.h>
#include <gdiplus.h>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

class Painter
{
public:
	Painter(HDC hdcWindow);
	void bar(int x1, int y1, int x2, int y2);
	void circle(int x, int y, int radius);
	void background(int x1, int y1, int x2, int y2);
private:
	HDC hdc;
};

