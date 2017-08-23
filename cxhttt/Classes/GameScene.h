#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TankController;
class MoveController;
class GameScene : public Layer
{
public:
	GameScene();
	virtual ~GameScene();
public:
	static Scene* createScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
private:
	void loadConfig();//加载地图，游戏背景音乐
	void loadController();
	int m_nLevel; // 哪一关
	TankController* m_tankCtr;
	MoveController* m_moveCtr;
};

