#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define BULLET_MAX_CACHE_NUM 10
class Bullet;
class TankBase;
class BombM;
class BulletManager : public Node
{
public:
	BulletManager();
	virtual ~BulletManager();
	Bullet* getAnyUnUsedBullet();
	static BulletManager* createWithID(TankBase* owner, int ID);
	bool initWithID(TankBase* owner, int ID);
	TankBase* getMyOwener();
	float getMyAtkDistance();
	BombM* getMyBombM();
	void changeRpg(int ID = 0);
private:
	TankBase* m_owner;
	Vector<Bullet*> m_BulletList;
	void createBulletsWithID(int ID);
	void update(float dt);
	void bulletLogicCheck(float dt);
	BombM* m_bombMgr;
};

