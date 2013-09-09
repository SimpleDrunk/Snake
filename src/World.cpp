#include "World.h"

const float World::TICK_INITIAL = 0.5f;
const float World::TICK_DECREMENT = 0.05f;

float World::tick = TICK_INITIAL;

World::World()
{
	snake = new Snake();
	srand(time(NULL));
	placeStain();
	bGameOver = false;
	score = 0;
	tickTime = 0;
}

World::~World()
{
	CC_SAFE_DELETE(snake);
}

void World::placeStain()
{
	for(int x=0; x<WORLD_WIDTH; x++)
	{
		for(int y=0; y<WORLD_HEIGHT; y++)
		{
			fields[x][y] = false;
		}
	}

	int len = snake->partArr->count();
	for(int i=0; i<len; i++)
	{
		SnakePart* part = (SnakePart*)snake->partArr->objectAtIndex(i);
		fields[part->x][part->y] = true;
	}

	int stainX = (int)(CCRANDOM_0_1()*WORLD_WIDTH);
	int stainY = (int)(CCRANDOM_0_1()*WORLD_HEIGHT);

	while(1)
	{
		if(fields[stainX][stainY] == false)
			break;
		stainX ++;
		if(stainX >= WORLD_WIDTH)
		{
			stainX = 0;
			stainY ++;
			if(stainY >= WORLD_HEIGHT)
			{
				stainY = 0;
			}
		}
	}

	stain = new Stain(stainX, stainY, (int)(CCRANDOM_0_1()*3));
}

void World::update(float dt)
{
	if(bGameOver)
		return;
	tickTime += dt;

	while(tickTime > tick)
	{
		tickTime -= tick;
		snake->advance();
		if(snake->checkBitten())
		{
			bGameOver = true;
			return;
		}
		SnakePart* head = (SnakePart*)snake->partArr->objectAtIndex(0);
		if(head->x == stain->x && head->y == stain->y)
		{
			score += SCORE_INCREMENT;
			snake->eat();
			//占满整个屏幕，神人？
			if(snake->partArr->count() == WORLD_WIDTH*WORLD_HEIGHT)
			{
				bGameOver = true;
				return;
			} else
			{
				placeStain();
			} if(score%100 == 0 && tick - TICK_DECREMENT > 0) //每得100分就要升级了，速度加快了！
			{
				tick -= TICK_DECREMENT; //间隔时间缩短了
			}
		}
	}
}