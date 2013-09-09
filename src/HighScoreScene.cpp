#include "HighScoreScene.h"
#include "Settings.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* HighScoreScene::scene()
{
	CCScene* scene = CCScene::create();
	HighScoreScene* layer = HighScoreScene::create();
	scene->addChild(layer);

	return scene;
}

bool HighScoreScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		background = CCSprite::create("background.png");
		background->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight/2));
		this->addChild(background, 0);

		tile = CCSprite::create("mainmenu.png", CCRectMake(0,42,192,42));
		CC_BREAK_IF(!tile);
		tile->setPosition(ccp(Settings::screenWidth/2,Settings::screenHeight-60));
		this->addChild(tile,1);

		for(int i=0; i<5; i++)
		{
			char* s = (char*)malloc(sizeof(char)*16);
			sprintf_s(s, 16, "%d. %d", i+1, Settings::highScores[i]);
			CCLabelTTF* label = CCLabelTTF::create(s, "Arial", 28);
			label->setAnchorPoint(ccp(0, 0.5));
			CC_BREAK_IF(!label);
			label->setColor(ccGRAY);
			label->setPosition(ccp(Settings::screenWidth/3, Settings::screenHeight - 120 - i*32));
			this->addChild(label, 1);
			free(s);			
		}

		this->setTouchEnabled(true);
		bRet = true;
	} while (0);

	return bRet;
}

void HighScoreScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(Settings::soundEnabled)
		SimpleAudioEngine::sharedEngine()->playEffect("click.mp3",false);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, MainMenuScene::scene()));
}