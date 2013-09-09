#ifndef __SNAKE_PART_H__
#define __SNAKE_PART_H__

#include "cocos2d.h"

class SnakePart : public cocos2d::CCNode
{
public:
	SnakePart(int x, int y);
	~SnakePart();

	int x, y;
};

#endif