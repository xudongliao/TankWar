#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GamePause :
	public cocos2d::Layer
{
public:
	GamePause();
	~GamePause();
public:
	virtual bool init( int rank);
	static cocos2d::Scene* createScene(RenderTexture* sqr,int rank);
	static GamePause* createWithLevel(int rank);
	//继续游戏  
	void menuContinue();
	//重新开始游戏  
	void menuRestart();
	//回主界面  
	void menuLogin();
private:
	int m_rank;
};

