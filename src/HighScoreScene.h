#ifndef __HIGH_SCORE_SCENE_H__
#define __HIGH_SCORE_SCENE_H__

#include "cocos2d.h"

class HighScoreScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HighScoreScene);

private:
	cocos2d::CCSprite* background;
	cocos2d::CCSprite* tile;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

};

#endif