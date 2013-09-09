#include "MainMenuScene.h"
#include "GameScene.h"
#include "HighScoreScene.h"
#include "HelpScene.h"
#include "Settings.h"

USING_NS_CC;
using namespace CocosDenshion;

CCRect MainMenuScene::playBounds = CCRectMake(64,Settings::screenHeight-220-42,192,42);
CCRect MainMenuScene::highScoresBounds = CCRectMake(64,Settings::screenHeight-220-42-42,192,42);
CCRect MainMenuScene::helpBounds = CCRectMake(64,Settings::screenHeight-220-42-42-42,192,42);
CCRect MainMenuScene::soundBounds = CCRectMake(0,0,64,64);

CCScene* MainMenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MainMenuScene *layer = MainMenuScene::create();
    scene->addChild(layer);

    return scene;
}

bool MainMenuScene::init()
{
	bool bRet = false;
	do 
	{
		if ( !CCLayer::init() )
		{
			return false;
		}
		Settings::load();    
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		Settings::screenWidth = screenSize.width;
		Settings::screenHeight = screenSize.height;

		//±³¾°
		background = CCSprite::create("background.png");
		CC_BREAK_IF(!background);
		background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
		this->addChild(background, 0);

		//ÓÎÏ·logo
		logo = CCSprite::create("logo.png");
		CC_BREAK_IF(!logo);
		logo->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight-100));
		this->addChild(logo, 1);

		//²Ëµ¥Í¼Æ¬
		menu = CCSprite::create("mainmenu.png");
		CC_BREAK_IF(!menu);
		menu->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight-284));
		this->addChild(menu, 1);


		//ÉùÒô°´Å¥
		soundOn = CCSprite::create("buttons.png", CCRectMake(0, 0, 64, 64));
		CC_BREAK_IF(!soundOn);
		soundOff = CCSprite::create("buttons.png", CCRectMake(64, 0, 64, 64));
		CC_BREAK_IF(!soundOff);
		soundOn->setPosition(ccp(32, 32));
		soundOff->setPosition(ccp(32, 32));

		soundOn->setVisible(Settings::soundEnabled);
		soundOff->setVisible(!Settings::soundEnabled);

		this->addChild(soundOn, 2);
		this->addChild(soundOff, 2);

		//ÒôĞ§
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("click.mp3");
		if(Settings::soundEnabled) {
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mp3", true);
		}

		this->setTouchEnabled(true);

		bRet = true;
	} while (0);
	  
    return bRet;
}

void MainMenuScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

	//play°´Å¥
	if(playBounds.containsPoint(touchPoint))
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, GameScene::scene()));
		return;
	}

	//ÅÅĞĞ°ñ°´Å¥
	if(highScoresBounds.containsPoint(touchPoint))
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, HighScoreScene::scene()));
		return;
	}

	//°ïÖú°´Å¥
	if(helpBounds.containsPoint(touchPoint))
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, HelpScene::scene()));
		return;
	}

	if(soundBounds.containsPoint(touchPoint))
	{
		Settings::soundEnabled = !Settings::soundEnabled;
		if(Settings::soundEnabled)
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mp3", true);
			soundOn->setVisible(true);
			soundOff->setVisible(false);
			Settings::save();
		} else
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			soundOn->setVisible(false);
			soundOff->setVisible(true);
			Settings::save();
		}
	}
	return;
}

