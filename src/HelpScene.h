#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

class HelpScene :
	public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HelpScene);
private:
	cocos2d::CCSprite *background;
	cocos2d::CCSprite *help, *help2, *help3;
	int helpIndex;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

#endif // __HELP_SCENE_H__