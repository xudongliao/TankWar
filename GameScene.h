#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "TankControl.h"
#include "BulletControl.h"
static int  GAME_SCENE_HEIGHT = 50;
static int  GAME_SCENE_WIDTH = 40;

using namespace CocosDenshion;
USING_NS_CC;
class GameScene :
	public cocos2d::Layer
{
private:
	int _count; //帧数计数器
	int _screenHeight, _screenWidth; //屏幕的高度和宽度
	int _score; //得分
	static TankControl* _tankControler;
	static BulletControl* _bulletControler;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	void update();
	void updateScore(int delta);
	static TankControl* getTankControler() { return _tankControler; };
	static BulletControl* getBulletControler() { return _bulletControler; };
};

	
