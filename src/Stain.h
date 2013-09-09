#ifndef __STAIN_H__
#define __STAIN_H__

#include "cocos2d.h"

class Stain : public cocos2d::CCNode
{
public:
	Stain(int x, int y, int type);
	~Stain();

	static const int TYPE_0 = 0;
	static const int TYPE_1 = 1;
	static const int TYPE_2 = 2;
	int x, y;
	int type;
};

#endif