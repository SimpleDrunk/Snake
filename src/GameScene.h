#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "World.h"

enum GameState
{
	kReady,
	kRunning,
	kPause,
	kGameOver
};

class GameScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameScene);
	virtual void update(float dt);

private:
	GameState gs;
	World* world;
	int oldScore;
	char score[16];
	float gapTime;
	cocos2d::CCArray* snakeArr;
	cocos2d::CCSprite* spStain;

	cocos2d::CCSprite* background;
	cocos2d::CCSprite* btnPause;
	cocos2d::CCSprite* btnClose;
	cocos2d::CCSprite* btnLeft;
	cocos2d::CCSprite* btnRight;
	cocos2d::CCSprite* readyMenu;
	cocos2d::CCSprite* pauseMenu;
	cocos2d::CCSprite* gameoverMenu;

	cocos2d::CCSpriteBatchNode *spriteBatch;
	cocos2d::CCLabelTTF* lbScore;

	cocos2d::CCRect btnPauseBounds;
	cocos2d::CCRect btnCloseBounds;
	cocos2d::CCRect btnLeftBounds;
	cocos2d::CCRect btnRightBounds;
	cocos2d::CCRect resumeBounds;
	cocos2d::CCRect quitBounds;

	void updateReady(float dt);
	void updateRunning(float dt);
	void updatePause(float dt);
	void updateGameOver(float dt);

	void setSnakeVisible(bool bVisible);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void drawSnake();
	void drawStain();
};



#endif __GAME_SCENE_H__