#include "Field.h"

#include "Painter.h"
#include <cstdlib>

Field::Field()
{
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x)
			m_[y][x] = EMPTY;
	newFruit();
}


void Field::setBlock(Type type, int x, int y)
{
	if (x > 0 && x < WIDTH && y>0 && y < HEIGHT)
		m_[y][x] = type;
}

Field::Type Field::block(int x, int y) const
{
	if (x - WIDTH / 15 >= xfruit || x + WIDTH / 15 <= xfruit || y + HEIGHT / 15 <= yfruit || y - HEIGHT / 15 >= yfruit)
	{
		return m_[y][x];
	}
	else if (xfruit == x && yfruit == y)
	{
		return m_[y][x];
	}
	else
	{
		return FRUIT;
	}


}

void Field::draw(Painter& p) const
{
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x)
		{
			switch (m_[y][x])
			{
			case EMPTY:
				break;
			case SNAKE_BLOCK:
				p.bar(x - WIDTH / 50,
					y - HEIGHT / 50,
					x + WIDTH / 50,
					y + HEIGHT / 50);
				break;
			case FRUIT:
				p.circle(x * BLOCK_WIDTH + BLOCK_WIDTH / 2,
					y * BLOCK_HEIGHT + BLOCK_HEIGHT / 2,
					HEIGHT / 50);
				break;
			}
		}
}

void Field::newFruit()
{
	setBlock(EMPTY, xfruit, yfruit);

	int a = 30;//границы спавна фрукта
	int b = HEIGHT-50;

	do
	{
		xfruit = a + rand() % (b - a);
		yfruit = a + rand() % (b - a);
	} while (block(xfruit, yfruit) != EMPTY);
	setBlock(FRUIT, xfruit, yfruit);
}
