#include "GameScene.h"
#include "Settings.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO 32

CCScene* GameScene::scene()
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		if(!CCLayer::init())
		{
			return false;
		}
		Settings::load();
		background = CCSprite::create("background.png");
		CC_BREAK_IF(!background);
		background->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight/2));
		this->addChild(background, 0);

		ccDrawLine(ccp(0, 416), ccp(320, 416));

		btnPause = CCSprite::create("buttons.png", CCRectMake(64, 128, 64, 64));
		CC_BREAK_IF(!btnPause);
		btnPause->setPosition(ccp(32, Settings::screenHeight - 32));
		btnPause->setVisible(false);
		this->addChild(btnPause, 1);

		btnClose = CCSprite::create("buttons.png", CCRectMake(0, 128, 64, 64));
		CC_BREAK_IF(!btnClose);
		btnClose->setPosition(ccp(Settings::screenWidth/2, 232));
		btnClose->setVisible(false);
		this->addChild(btnClose, 1);

		btnLeft = CCSprite::create("buttons.png", CCRectMake(64, 64, 64, 64));
		CC_BREAK_IF(!btnLeft);
		btnLeft->setPosition(ccp(32, 32));
		btnLeft->setVisible(false);
		this->addChild(btnLeft, 1);

		btnRight = CCSprite::create("buttons.png", CCRectMake(0, 64, 64, 64));
		CC_BREAK_IF(!btnRight);
		btnRight->setPosition(ccp(Settings::screenWidth-32, 32));
		btnRight->setVisible(false);
		this->addChild(btnRight, 1);

		readyMenu = CCSprite::create("ready.png");
		CC_BREAK_IF(!readyMenu);
		readyMenu->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight-148));
		this->addChild(readyMenu, 1);

		pauseMenu=CCSprite::create("pausemenu.png");
		CC_BREAK_IF(!pauseMenu);
		pauseMenu->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight-148));
		pauseMenu->setVisible(false);
		this->addChild(pauseMenu, 1);

		gameoverMenu=CCSprite::create("gameover.png");
		CC_BREAK_IF(!gameoverMenu);
		gameoverMenu->setPosition(ccp(Settings::screenWidth/2, Settings::screenHeight-125));
		gameoverMenu->setVisible(false);
		this->addChild(gameoverMenu, 1);

		//初始化游戏数据
		world = new World();
		CC_BREAK_IF(!world);
		spriteBatch = CCSpriteBatchNode::create("snake.png");
		CC_BREAK_IF(!spriteBatch);
		this->addChild(spriteBatch);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("snake.plist");

		Snake* snake = world->snake;
		CC_BREAK_IF(!snake);
		CCArray* partArr = snake->partArr;
		CC_BREAK_IF(!partArr);
		int len = partArr->count();
		snakeArr = CCArray::createWithCapacity(len);
		snakeArr->retain();
		SnakePart* part = (SnakePart*)partArr->objectAtIndex(0);
		CCSprite* headSprite = CCSprite::createWithSpriteFrameName("headup.png");
		CC_BREAK_IF(!headSprite);
		headSprite->setPosition(ccp(part->x*PTM_RATIO+PTM_RATIO/2, Settings::screenHeight-part->y*PTM_RATIO+PTM_RATIO/2));
		headSprite->setVisible(false);
		snakeArr->addObject(headSprite);
		spriteBatch->addChild(headSprite);

		for(int i=1; i<len; i++)
		{
			part = (SnakePart*)world->snake->partArr->objectAtIndex(i);
			CCSprite* partSprite = CCSprite::createWithSpriteFrameName("tail.png");
			partSprite->setPosition(ccp(part->x*PTM_RATIO+PTM_RATIO/2, Settings::screenHeight-part->y*PTM_RATIO-PTM_RATIO/2)); //??
			partSprite->setVisible(false);
			snakeArr->addObject(partSprite);
			spriteBatch->addChild(partSprite);
		}

		//食物来啦stain
		spStain = CCSprite::createWithSpriteFrameName("stain1.png");
		CC_BREAK_IF(!spStain);
		spStain->setPosition(ccp(world->stain->x*PTM_RATIO + PTM_RATIO/2, Settings::screenHeight - world->stain->y*PTM_RATIO-PTM_RATIO/2));//??
		spriteBatch->addChild(spStain);

		//分数
		memset(score, 0x00, 16);
		sprintf_s(score, 16, "score: %d", 0);				//学习了
		lbScore = CCLabelTTF::create(score, "Arial", 32);
		CC_BREAK_IF(!lbScore);
		lbScore->setPosition(ccp(Settings::screenWidth/2, 32));
		this->addChild(lbScore, 1);

		//音效
		SimpleAudioEngine::sharedEngine()->preloadEffect("click.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("eat.mp3");

		gs = kReady;
		oldScore = 0;
		gapTime = 0;

		//按钮区域
		btnPauseBounds = CCRectMake(0, Settings::screenHeight-64, 64, 64);
		btnCloseBounds = CCRectMake(Settings::screenWidth/2-32, 200, 64, 64);
		btnLeftBounds = CCRectMake(0, 0, 64, 64);
		btnRightBounds = CCRectMake(Settings::screenWidth-64, 0, 64, 64);
		resumeBounds = CCRectMake(Settings::screenWidth/2-80, Settings::screenHeight-148, 160, 48);
		quitBounds = CCRectMake(Settings::screenWidth/2-80, Settings::screenHeight-196, 160, 48);


		this->setTouchEnabled(true);
		this->scheduleUpdate();

		bRet = true;
	} while (0);
	
	return bRet;
}

void GameScene::update(float dt)
{
	if(gs == kReady)
		updateReady(dt);
	if(gs == kRunning)
		updateRunning(dt);
	if(gs == kPause)
		updatePause(dt);
	if(gs == kGameOver)
		updateGameOver(dt);
	gapTime += dt;
	if(gapTime > 0.2f)
	{
		if((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
		{
			world->snake->turnLeft();
			gapTime = 0.0f;
		}
		if((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
		{
			world->snake->turnRight();
			gapTime = 0.0f;
		}
	}
}
	

void GameScene::updateReady(float dt)
{
	btnPause->setVisible(false);
	btnClose->setVisible(false);
	btnLeft->setVisible(false);
	btnRight->setVisible(false);
	readyMenu->setVisible(true);
	pauseMenu->setVisible(false);
	gameoverMenu->setVisible(false);
	this->setSnakeVisible(false);
}

void GameScene::updateRunning(float dt)
{
	btnPause->setVisible(true);
	btnClose->setVisible(false);
	btnLeft->setVisible(true);
	btnRight->setVisible(true);
	readyMenu->setVisible(false);
	pauseMenu->setVisible(false);
	gameoverMenu->setVisible(false);
	this->setSnakeVisible(true);
	this->drawStain();
	this->drawSnake();
	world->update(dt);
	if(world->bGameOver)
	{
		gs = kGameOver;
	}
}

void GameScene::updatePause(float dt)
{
	btnPause->setVisible(false);
	btnClose->setVisible(false);
	btnLeft->setVisible(false);
	btnRight->setVisible(false);
	readyMenu->setVisible(false);
	pauseMenu->setVisible(true);
	gameoverMenu->setVisible(false);
	this->setSnakeVisible(false);
}

void GameScene::updateGameOver(float dt)
{
	btnPause->setVisible(false);
	btnClose->setVisible(true);
	btnLeft->setVisible(false);
	btnRight->setVisible(false);
	readyMenu->setVisible(false);
	pauseMenu->setVisible(false);
	gameoverMenu->setVisible(true);
	this->setSnakeVisible(false);

}

void GameScene::setSnakeVisible(bool bVisible)
{
	int len = snakeArr->count();
	for(int i=0;i<len;i++)
	{
		CCSprite *snakeSprite = (CCSprite*)snakeArr->objectAtIndex(i);
		snakeSprite->setVisible(bVisible);
	}
}

void GameScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

	if(gs == kReady)
	{
		gs = kRunning;
	}
	if(gs == kRunning)
	{
		if(btnLeftBounds.containsPoint(touchPoint))
		{
			world->snake->turnLeft();
			SimpleAudioEngine::sharedEngine()->playEffect("click.mp3",false);
		}
		if(btnRightBounds.containsPoint(touchPoint))
		{
			world->snake->turnRight();
			SimpleAudioEngine::sharedEngine()->playEffect("click.mp3",false);
		}
		if(btnPauseBounds.containsPoint(touchPoint))
		{
			gs = kPause;
		}
	}
	if(gs == kPause)
	{
		if(resumeBounds.containsPoint(touchPoint))
		{
			gs = kRunning;
		}
		if(quitBounds.containsPoint(touchPoint))
		{
			gs = kGameOver;
			this->snakeArr->removeAllObjects();
			free(world);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, MainMenuScene::scene()));
			return;
		}
	}
	if(gs == kGameOver)
	{
		if(btnCloseBounds.containsPoint(touchPoint))
		{
			if(oldScore!=world->score)
			{
				oldScore=world->score;
				sprintf_s(score, 16, "score: %d", oldScore);
				SimpleAudioEngine::sharedEngine()->playEffect("eat.mp3",false);
				lbScore->setString(score);
				if(oldScore > Settings::highScores[4])
				{
					Settings::highScores[4] = oldScore;
					for(int i=4; i>0; i--)
					{
						for(int j=i-1; j>=0; j--)
						{
							if(Settings::highScores[j] < Settings::highScores[i])
							{
								int tmp = Settings::highScores[i];
								Settings::highScores[i] = Settings::highScores[j];
								Settings::highScores[j] = tmp;
							}
						}
					}
					Settings::save();
				}
			}
			this->snakeArr->removeAllObjects();
			free(world);
			world = new World();
			gs = kReady;
		}
	}

}

void GameScene::drawSnake()
{
	Snake* snake = world->snake;
	CCArray* partArr = snake->partArr;
	int len = partArr->count();
	int slen = snakeArr->count();

	if(oldScore!=world->score)
	{
		oldScore=world->score;
		sprintf_s(score, 16, "score: %d", oldScore);
		SimpleAudioEngine::sharedEngine()->playEffect("eat.mp3",false);
		lbScore->setString(score);
	}

	if(slen < len)
	{
		CCSprite* spTail = CCSprite::createWithSpriteFrameName("tail.png");
		snakeArr->addObject(spTail);
		spriteBatch->addChild(spTail);
	}

	SnakePart* head = (SnakePart*)partArr->objectAtIndex(0);
	CCSprite* spHead = (CCSprite*)snakeArr->objectAtIndex(0);
	if(snake->direction == Snake::UP) //蛇脑袋的方向不一样，图也不一样哦
	{
		CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("headup.png");
		spHead->setDisplayFrame(frame);
	}
	else if(snake->direction==Snake::DOWN)
	{
		CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("headdown.png");
		spHead->setDisplayFrame(frame);
	}
	else if(snake->direction==Snake::LEFT)
	{
		CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("headleft.png");
		spHead->setDisplayFrame(frame);
	}
	else if(snake->direction==Snake::RIGHT)
	{
		CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("headright.png");
		spHead->setDisplayFrame(frame);
	}

	for(int i=0;i<slen;i++)
	{
		SnakePart* part = (SnakePart*)partArr->objectAtIndex(i);
		CCSprite* spPart = (CCSprite*)snakeArr->objectAtIndex(i);
		spPart->setPosition(ccp(part->x*PTM_RATIO+PTM_RATIO/2, Settings::screenHeight-part->y*PTM_RATIO-PTM_RATIO/2));
	}
}

void GameScene::drawStain()
{
	Stain* st = world->stain;
	if(st->type == Stain::TYPE_0)
	{
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("stain1.png");
		spStain->setDisplayFrame(frame);
	} else if(st->type == Stain::TYPE_1)
	{
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("stain2.png");
		spStain->setDisplayFrame(frame);
	} else if(st->type == Stain::TYPE_2)
	{
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("stain3.png");
		spStain->setDisplayFrame(frame);
	}
	spStain->setPosition(ccp(st->x*PTM_RATIO+PTM_RATIO/2, Settings::screenHeight-st->y*PTM_RATIO-PTM_RATIO/2));
}