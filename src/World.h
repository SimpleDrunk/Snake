#ifndef __WORLD_H__
#define __WORLD_H__

#include "Snake.h"
#include "Stain.h"
#include "cocos2d.h"

class World : public cocos2d::CCNode
{
public:
	World();
	~World();

	static const int WORLD_WIDTH = 10;
	static const int WORLD_HEIGHT = 13;
	static const int SCORE_INCREMENT = 10;
	static const float TICK_INITIAL;
	static const float TICK_DECREMENT;

	bool bGameOver;
	int score;

	void update(float dt);
	Snake* snake;
	Stain* stain;

private:
	bool fields[WORLD_WIDTH][WORLD_HEIGHT];
	float tickTime;
	static float tick;

	void placeStain();
};






#endif