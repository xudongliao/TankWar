#pragma once
#include "cocos2d.h"


USING_NS_CC;
class HeroTank;
class TankController : public Node
{
public:
	TankController();
	virtual ~TankController();
	
private:
	HeroTank* m_Tank;
	Vector<HeroTank*> m_tanks; 
	Vector<HeroTank*>  m_enemyTanks;
public:
	static TankController* creatTankCtrWithLevel(int nLevel, TMXTiledMap*);
	virtual bool initTankCtrWithLevel(int nLevel, TMXTiledMap* map);

	//stephen
	Vector<HeroTank*> &getTanks() { return m_tanks; };  // get all tanks,include playertank and enemytanks
	HeroTank*  getPlayerTank() { return m_Tank; };
	Vector<HeroTank*> &getEnemyTanks() { return m_enemyTanks; };

};

