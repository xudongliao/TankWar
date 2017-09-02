#pragma once
#include "TankBase.h"
#include "cocos2d.h"
USING_NS_CC;
class HomeBase:public TankBase
{
public:
	HomeBase();
	virtual ~HomeBase();
public:
	static HomeBase* CreateWithLevel(int nLevel);
	bool initWithLevel(int nLevel );
	void onDead() override;
};

