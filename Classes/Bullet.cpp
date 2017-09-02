#include "Bullet.h"
#include "cocos2d.h"
#include "CsvUtil.h"
#include "EnumBulletConfType.h"
#include "BulletManager.h"
#include "soundEngine.h"
#include "TankController.h"
#include "BombM.h"
#include "gvarible.h"
#include "TankBase.h"

Bullet * Bullet::create(int ID)
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->init(ID)) {
		bullet->autorelease();
	}
	else {
		CC_SAFE_DELETE(bullet);
	}
	return bullet;
}


bool Bullet::init(int ID) {
	bool bRet = false;
	do 
	{
		//属性初始化
		auto csvutil = CsvUtil::getInstance();
		std::string sBulletID = StringUtils::format("%d", ID);
		std::string sBulletConfig = "csv/BulletConfig.csv";
		int nLine = csvutil->findValueInWithLine(sBulletID.c_str(), enumBulletID, sBulletConfig.c_str());
		CC_BREAK_IF(nLine < 0);
		this->setnID(ID);
		setnSpeed(csvutil->getFloat(nLine, enumBulletSpeed, sBulletConfig.c_str()));
		setsName(csvutil->getValue(nLine, enumBulletName, sBulletConfig.c_str()).asString());
		setfDistance(csvutil->getFloat(nLine, enumBulletAtkDistance, sBulletConfig.c_str()));
		//图片绑定
		auto bullet = Sprite::create(StringUtils::format("Sprite/Bullet/Bullet_%d.png", ID));
		bindSprite(bullet);
		bRet = true;	  
		
	} while (0);
	return bRet;
}

void Bullet::Move(double angle)
{
	this->setRotation(angle * 180 /3.141);
	m_isArrive = false;
	float time = m_fDistance/m_nSpeed/ 60;
	Point pos = this->getPosition();
	pos.x += m_fDistance * sin(angle);
	pos.y += m_fDistance * cos(angle);

	auto moveTo = MoveTo::create(time, pos);
	auto callfunc = CallFunc::create([&]() {
		m_isArrive = true;
	});

	auto actions = Sequence::create(moveTo, callfunc, NULL);
	this->runAction(actions);
}

void Bullet::Move(Point pos)
{
	m_isArrive = false;
	float time = m_fDistance / m_nSpeed / 60;
	auto moveTo = MoveTo::create(time, pos);
	auto callfunc = CallFunc::create([&]() {
		m_isArrive = true;
	});

	auto actions = Sequence::create(moveTo, callfunc, NULL);
	this->runAction(actions);
}

bool Bullet::collideWithOthers()
{
		Point pos = this->getParent()->convertToWorldSpace(this->getPosition());
		auto tank = ((BulletManager*)this->getParent())->getMyOwener();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		BombM* myBombMgr = ((BulletManager*)this->getParent())->getMyBombM();
		if (pos.x <0 || pos.y <0 || pos.x >visibleSize.width || pos.y > visibleSize.height)
		{
			return true;
		}
		if (tank->isTileValue("isIron", pos, "true"))
		{
			myBombMgr->createBomb(kBulletBomb, this->getPosition());
			return true;
		}
		if (tank->isTileValue("isWall", pos, "true"))
		{
			Point tiledPos = tank->tileCordForPosition(pos);
			tank->getMap()->getLayer("bricks")->removeTileAt(tiledPos);
			tank->getMap()->getLayer("META")->removeTileAt(tiledPos);
			myBombMgr->createBomb(kBulletBomb, this->getPosition());

			TankController* myTankCtr = (TankController*)(this->getParent()->getParent()->getParent());
			auto rand = RandomHelper();
			int randIndex = rand.random_int(0, 100);
			if (randIndex < 8)
			{
				
				Point pos = this->getParent()->convertToWorldSpace(this->getPosition());
				myTankCtr->CreateCube(pos);
			}
			return true;
		}

		
		auto TargetTank = ((TankController*)tank->getParent())->isWithinAnyTank(pos);
	
		if (TargetTank != NULL && TargetTank != tank)
		{
			if (!TargetTank->getUnAtkable())
			{
				TargetTank->hurtMe(tank->getnAtkValue());
				return true;
			}
		}
		return false;
}

bool Bullet::RPGcollideWithOthers()
{
	Point pos = this->getParent()->convertToWorldSpace(this->getPosition());
	auto tank = ((BulletManager*)this->getParent())->getMyOwener();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	BombM* myBombMgr = ((BulletManager*)this->getParent())->getMyBombM();

	Point Pos[9];
	Pos[0] = pos;
	Pos[1] = Point(Pos[0].x + 30, Pos[0].y + 30);
	Pos[2] = Point(Pos[0].x + 30, Pos[0].y - 30);
	Pos[3] = Point(Pos[0].x + 30, Pos[0].y );
	Pos[4] = Point(Pos[0].x - 30, Pos[0].y + 30);
	Pos[5] = Point(Pos[0].x - 30, Pos[0].y - 30);
	Pos[6] = Point(Pos[0].x - 30, Pos[0].y );
	Pos[7] = Point(Pos[0].x , Pos[0].y + 30);
	Pos[8] = Point(Pos[0].x , Pos[0].y- 30);

	if (pos.x <0 || pos.y <0 || pos.x >visibleSize.width || pos.y > visibleSize.height)
	{
		return true;
	}

	if (tank->isTileValue("isWall", pos, "true") ||
		tank->isTileValue("isIron", pos, "true"))
	{
		for (int i = 0; i <= 8; i++)
		{
			if (Pos[i].x <0 || Pos[i].y <0 || Pos[i].x >visibleSize.width || Pos[i].y > visibleSize.height)
			{
				continue;
			}
			Point tiledPos = tank->tileCordForPosition(Pos[i]);
			if (tank->isTileValue("isWall", Pos[i], "true"))
			{
				tank->getMap()->getLayer("bricks")->removeTileAt(tiledPos);
				tank->getMap()->getLayer("META")->removeTileAt(tiledPos);
			}
			else if (tank->isTileValue("isIron", Pos[i], "true"))
			{
				tank->getMap()->getLayer("iron")->removeTileAt(tiledPos);
				tank->getMap()->getLayer("META")->removeTileAt(tiledPos);
			}
			myBombMgr->createBomb(kEnemyTankBomb, this->getPosition());
			soundEngine::KindsOfSE("music/dead.mp3", (double)g_SEpercent / 100);
		}
		

		TankController* myTankCtr = (TankController*)(this->getParent()->getParent()->getParent());
		auto rand = RandomHelper();
		int randIndex = rand.random_int(0, 100);
		if (randIndex < 8)
		{
			Point pos = this->getParent()->convertToWorldSpace(this->getPosition());
			myTankCtr->CreateCube(pos);
		}
		return true;
	}


	auto TargetTank = ((TankController*)tank->getParent())->isWithinAnyTank(pos);

	if (TargetTank != NULL && TargetTank != tank)
	{
		if (!TargetTank->getUnAtkable())
		{
			TargetTank->hurtMe(1000000);
			return true;
		}
	}
	return false;
}

void Bullet::setUsed(bool isUsed)
{
	this->m_isUsed = isUsed;
	if (isUsed == false)
	{
		this->removeChildByTag(3);
	}
	setVisible(isUsed);
}

bool Bullet::isUsed()
{
	return m_isUsed;
}

bool Bullet::isArrive()
{
	if (m_nID == 0)
	{
		if (RPGcollideWithOthers()) {
			soundEngine::KindsOfSE("music/bullet.mp3", (double)g_SEpercent/100);
			m_isArrive = true;
		}
		return m_isArrive;
	}else
	if (collideWithOthers()) {
		soundEngine::KindsOfSE("music/bullet.mp3", (double)g_SEpercent / 100);
		m_isArrive = true;
	}
	return m_isArrive;
}





