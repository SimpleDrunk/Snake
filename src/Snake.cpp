#include "Snake.h"

USING_NS_CC;

Snake::Snake()
{
	partArr = CCArray::createWithCapacity(3);
	partArr->retain();
	direction = Snake::UP;
	partArr->addObject(new SnakePart(5, 6));
	partArr->addObject(new SnakePart(5, 7));
	partArr->addObject(new SnakePart(5, 8));
}

Snake::~Snake()
{
	int length = partArr->count();
	for(int i=0; i<length; i++)
	{
		SnakePart* part = (SnakePart*)partArr->objectAtIndex(i);
		CC_SAFE_DELETE(part);
	}
	partArr->removeAllObjects();
	partArr->release();
}

//左转
void Snake::turnLeft()
{
	direction++;
	if(direction > RIGHT)
	{
		direction = UP;
	}
}

//右转
void Snake::turnRight()
{
	direction--;
	if(direction < UP)
	{
		direction = RIGHT;
	}
}

//吃东西了
void Snake::eat()
{
	int len = partArr->count();
	SnakePart* end = (SnakePart*)partArr->objectAtIndex(len-1);
	partArr->addObject(new SnakePart(end->x, end->y));
}

//蛇蛇动起来！
void Snake::advance()
{
	SnakePart* head = (SnakePart*)partArr->objectAtIndex(0);
	int len = partArr->count() - 1;
	for(int i=len; i>0; i--)
	{
		SnakePart* before = (SnakePart*)partArr->objectAtIndex(i-1);
		SnakePart* part = (SnakePart*)partArr->objectAtIndex(i);
		part->x = before->x;
		part->y = before->y;
	}
	if(direction == UP)
		head->y -= 1;
	if(direction == LEFT)
		head->x -= 1;
	if(direction == DOWN)
		head->y += 1;
	if(direction == RIGHT)
		head->x += 1;

	if(head->x < 0)
		head->x = 9;
	if(head->x > 9)
		head->x = 0;
	if(head->y < 0)
		head->y = 12;
	if(head->y > 12)
		head->y = 0;
}

//咬到自己了？
bool Snake::checkBitten()
{
	int len = partArr->count();
	SnakePart* head = (SnakePart*)partArr->objectAtIndex(0);
	for(int i=1; i<len; i++)
	{
		SnakePart* part = (SnakePart*)partArr->objectAtIndex(i);
		if(part->x == head->x && part->y == head->y)
			return true;
	}
	return false;
}