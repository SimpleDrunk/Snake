#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class MainMenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MainMenuScene);

private:
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	static cocos2d::CCRect MainMenuScene::playBounds;
	static cocos2d::CCRect MainMenuScene::highScoresBounds;
	static cocos2d::CCRect MainMenuScene::helpBounds;
	static cocos2d::CCRect MainMenuScene::soundBounds;

	cocos2d::CCSprite *background;
	cocos2d::CCSprite *logo;
	cocos2d::CCSprite *menu;
	cocos2d::CCSprite *soundOn;
	cocos2d::CCSprite *soundOff;

};

#endif // __MAIN_MENU_SCENE_H__
