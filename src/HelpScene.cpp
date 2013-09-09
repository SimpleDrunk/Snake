#include "HelpScene.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* HelpScene::scene()
{
	CCScene *scene = CCScene::create();
	HelpScene *layer = HelpScene::create();
	scene->addChild(layer);

	return scene;
}
bool HelpScene::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		background = CCSprite::create("background.png");
		CC_BREAK_IF(!background);
		background->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight/2));
		this->addChild(background, 0);

		help = CCSprite::create("help1.png");
		CC_BREAK_IF(!help);
		help->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight/2));
		this->addChild(help, 1);

		help2 = CCSprite::create("help2.png");
		CC_BREAK_IF(!help2);
		help2->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight/2));
		help2->setVisible(false);
		this->addChild(help2, 1);

		help3 = CCSprite::create("help3.png");
		CC_BREAK_IF(!help3);
		help3->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight/2));
		help3->setVisible(false);
		this->addChild(help3, 1);

		helpIndex = 1;
		SimpleAudioEngine::sharedEngine()->preloadEffect("click.mp3");

		this->setTouchEnabled(true);
		bRet=true;
	}while(0);

	return bRet;
}

void HelpScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(Settings::soundEnabled)
		SimpleAudioEngine::sharedEngine()->playEffect("click.mp3",false);
	helpIndex++;

	if(helpIndex >= 4)
	{
		helpIndex = 1;
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, MainMenuScene::scene()));
		return;
	}

	if(helpIndex == 2)
	{
		help->setVisible(false);
		help2->setVisible(true);
		help3->setVisible(false);
	} else if(helpIndex == 3)
	{
		help->setVisible(false);
		help2->setVisible(false);
		help3->setVisible(true);
	}
}