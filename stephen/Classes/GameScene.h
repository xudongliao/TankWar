#pragma once
#include "cocos2d.h"
#include "MoveController.h"
#include "TankController.h"
#include "TankCanon.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Joystick.h"
USING_NS_CC;
class BulletControl;
class GameScene : public Layer
{
public:
	GameScene();
	virtual ~GameScene();
public:
	static Scene* createScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	static TankController* getTankController() {
		return m_tankCtr;
	};
	static  MoveController* getMoveController() { return m_moveCtr; };
	static BulletControl* getBulletController() { return m_bulletCtr; };

private:
	void loadConfig();//加载地图，游戏背景音乐
	void loadController();
	int m_nLevel; // 哪一关
	static TankController* m_tankCtr ;
	static MoveController* m_moveCtr ;
	static BulletControl* m_bulletCtr;
};

