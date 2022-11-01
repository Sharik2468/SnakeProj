#pragma once
#include "Snake.h"
#include "Field.h"

class Game
{
public:
	void tick();
	void draw(Painter&) const;
	void keyEvent(Snake::Direction);
private:
	Field field_;
	Snake snake_;
};

