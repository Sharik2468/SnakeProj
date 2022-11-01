#pragma once

class Painter;

class Field
{
public:
	enum { WIDTH = 500, HEIGHT = 500 };
	enum { BLOCK_WIDTH = 1, BLOCK_HEIGHT = 1 };
	enum Type { EMPTY, SNAKE_BLOCK, FRUIT };
	Field();
	void setBlock(Type type, int x, int y);
	Type block(int x, int y) const;
	void draw(Painter&) const;
	void newFruit();
private:
	Type m_[HEIGHT][WIDTH];
	int xfruit, yfruit;
};

