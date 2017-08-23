#pragma once
#include "cocos2d.h"
#include "HeroTank.h"
USING_NS_CC;
class TankController : public Node
{
public:
	TankController();
	virtual ~TankController();
public:
	static TankController* creatTankCtrWithLevel(int nLevel, TMXTiledMap*);
	virtual bool initTankCtrWithLevel(int nLevel, TMXTiledMap* map);
public:
	HeroTank* m_Tank;

};

