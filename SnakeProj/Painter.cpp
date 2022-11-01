#include "Painter.h"

Painter::Painter(HDC hdcWindow)
{
	hdc = hdcWindow;
}

void Painter::bar(int x1, int y1, int x2, int y2)
{
	Graphics graphics(hdc);

	// Create a Pen object.
	Pen blackPen(Color(255, 0, 0, 0), 3);

	// Create a RectF object.
	RectF rect(x1 - abs(x2 - x1)/2, y1 - abs(y2 - y1)/2, abs(x2 - x1), abs(y2 - y1));

	// Draw rect.
	graphics.DrawRectangle(&blackPen, rect);

	graphics.DrawEllipse(&blackPen, x1, y1, 1, 1);
}

void Painter::circle(int x, int y, int radius)
{
	Graphics graphics(hdc);

	// Create a Pen object.
	Pen blackPen(Color(255, 0, 0, 0), 3);

	// Draw rect.
	graphics.DrawEllipse(&blackPen, x, y, radius, radius);
}

void Painter::background(int x1, int y1, int x2, int y2)
{
	Graphics graphics(hdc);

	SolidBrush brush(Color(255, 255, 255));

	graphics.FillRectangle(&brush, x1, y1, x2, y2);
}
