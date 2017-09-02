#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "EnumEndType.h"
USING_NS_CC;
class GameScene;
class GameOver :
	public cocos2d::LayerColor
{
public:
	GameOver();
	~GameOver();
public:
	/*EndType 包括GAMEWIN 和 GAMEFAIL，根据游戏的结束方式传递不同的值*/
	static Scene* createSceneWithLevel(EndType endType, int Level, GameScene* );
	virtual bool initWithLevel(EndType endType, int Level, GameScene*);
	static GameOver* createWithLevel(EndType endType, int nLevel, GameScene*);
	void setMyScene(GameScene*);
	GameScene* m_gameScene;
};

