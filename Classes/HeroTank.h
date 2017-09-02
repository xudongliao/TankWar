#pragma once
#include "cocos2d.h"
#include "TankBase.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class TankCanon;
class HeroTank : public TankBase
{
public:
	HeroTank();
	virtual ~HeroTank();
public:
	static HeroTank* createFromCsvFileByID(int ID);
	bool initFromCsvFileByID(int ID);
	void onDead() override;

};

