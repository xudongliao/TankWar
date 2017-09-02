#pragma once
#include "cocos2d.h"
#include "HeroTank.h"
#include "EnemyTank.h"
#include "SpecialCube.h"
USING_NS_CC;
class HomeBase;
class BombM;
class TankController : public Node
{
public:
	TankController();
	virtual ~TankController();
//己方坦克
public:
	static TankController* creatTankCtrWithLevel(int nLevel, TMXTiledMap*);
	virtual bool initTankCtrWithLevel(int nLevel, TMXTiledMap* map);
public:
	HeroTank* getMyTank();
public:
	void CreateCanon(TMXTiledMap*);
	void CreateHeroTank(int, TMXTiledMap*);
	void CreateEnemyTank(int, TMXTiledMap* );
	void CreateHome(int, TMXTiledMap*);
	void CreateCube(Point pos);
	TankBase* isWithinAnyTank(Point pos);
	SpecialCube* isWithinAnyCube(Point pos);
	bool isCloseToHeroTank(Point pos, float distance);
	bool isCloseToHomeBase(Point, float);
	int getNotToShowEnemyNum();
//敌方坦克
private:
	Vector<TankBase*> m_AllTankList;
	Vector<TankBase*> m_EnemyTankList;
	Vector<TankBase*> m_NotShowTankEnemyList;
	Vector<SpecialCube*> m_SpecialCubeList;
	void update(float dt);
	float m_floatShowTimeCount;
	HeroTank* m_Tank;
	HomeBase* m_Home;
	BombM* m_BombMgr;
public:
	void deleteCube(SpecialCube*);
	BombM* getMyBombMgr();
};

