#include "BulletManager.h"
#include "Bullet.h"
#include "BombM.h"

BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

Bullet * BulletManager::getAnyUnUsedBullet()
{
	for (auto bullet : m_BulletList) {
		if (bullet->isUsed() == false)
		{
			bullet->setUsed(true);
			return bullet;
		}
	}
	return NULL;
}

BulletManager * BulletManager::createWithID(TankBase * owner, int ID)
{
	BulletManager* bulletMgr = new BulletManager();
	if (bulletMgr && bulletMgr->initWithID(owner,ID))
	{
		bulletMgr->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletMgr);
	}
	return bulletMgr;
}

bool BulletManager::initWithID(TankBase * owner, int ID)
{
	m_owner = owner;
	createBulletsWithID(ID);
	m_bombMgr = BombM::create();
	this->addChild(m_bombMgr);
	this->scheduleUpdate();
	return true;
}

TankBase * BulletManager::getMyOwener()
{
	return m_owner;
}

float BulletManager::getMyAtkDistance()
{
	Bullet* myBullet = NULL;
	for (auto bullet: m_BulletList) {
		myBullet = bullet;
		break;
	}
	return myBullet->getfDistance();
}

BombM * BulletManager::getMyBombM()
{
	return m_bombMgr;
}

void BulletManager::changeRpg(int ID)
{
	for (auto bullet: m_BulletList)
	{
		bullet->removeAllChildren();
		bullet->init(ID);
		
	}
}

void BulletManager::createBulletsWithID(int ID)
{
	Bullet*  bullet = NULL;
	for (int i = 0; i < BULLET_MAX_CACHE_NUM; i++) {
		bullet = Bullet::create(ID);
		bullet->setUsed(false);
		m_BulletList.pushBack(bullet);
		addChild(bullet);
	}
}

void BulletManager::update(float dt)
{
	bulletLogicCheck(dt);
}

void BulletManager::bulletLogicCheck(float dt)
{
	for (auto bullet : m_BulletList) {
		this;
		if (bullet->isUsed() == true)
		{
			if (bullet->isArrive())
			{
				bullet->setUsed(false);
			}
		}
	}
}

