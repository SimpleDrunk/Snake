#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "cocos2d.h"
#include "SnakePart.h"

class Snake : public cocos2d::CCNode
{
public:
	Snake();
	~Snake();

	static const int UP = 0;
	static const int LEFT = 1;
	static const int DOWN = 2;
	static const int RIGHT = 3;

	cocos2d::CCArray* partArr;
	int direction;

	void turnLeft();
	void turnRight();
	void eat();
	void advance();
	bool checkBitten();
};

#endif