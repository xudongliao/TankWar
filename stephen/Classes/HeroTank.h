#pragma once
#include "cocos2d.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Entity.h"
#include "GameScene.h"
USING_NS_CC;
//class BulletController;
class TankCanon;
class HeroTank : public Entity
{
public:
	HeroTank();
	virtual ~HeroTank();
public:
	CREATE_FUNC(HeroTank);
	virtual bool init();
	static HeroTank* createFromCsvFileByID(int ID);
	bool initFromCsvFileByID(int ID);
	TankCanon* m_Tankcanon;
	void TankRotation(double);
	void shoot();
protected:
	virtual void onDead();
	virtual void onHurt();

private:
	ui::LoadingBar*m_hpBar();
	void atk();
	TMXTiledMap* m_map;
	//BulletController* m_BulletController;
	
};

