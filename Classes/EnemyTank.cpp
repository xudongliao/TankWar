#include "EnemyTank.h"
#include "TankCanon.h"
#include "CsvUtil.h"
#include "EnumTankTypeConfig.h"
#include "BulletManager.h"
#include "TankController.h"
#include "BombM.h"
#include "GlobeDefine.h"
EnemyTank::EnemyTank()
{
	m_isDead = false;
	m_isShowUp = false;
}

EnemyTank::~EnemyTank()
{
}

EnemyTank * EnemyTank::createFromCsvFileByID(int ID, float fShowTime, Point pos)
{
	EnemyTank* myEnemyTank = new EnemyTank();
	if (myEnemyTank && myEnemyTank->initFromCsvFlieByID(ID, fShowTime, pos))
	{
		myEnemyTank->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(myEnemyTank);
	}
	return myEnemyTank;
}

bool EnemyTank::initFromCsvFlieByID(int ID, float fShowTime, Point pos)
{
	bool bRet = false;
	do 
	{
		auto csvutil = CsvUtil::getInstance();
		std::string sEnemyID = StringUtils::format("%d",ID);
		int nLine = csvutil->findValueInWithLine(sEnemyID.c_str(), enumTankID, "csv/TankConfig.csv");
		CC_BREAK_IF(nLine < 0);
		setnID(ID);
		setnHp(csvutil->getInt(nLine, enumTankHp, "csv/TankConfig.csv"));
		setfCoolDownTime(csvutil->getFloat(nLine, enumTankCoolDownTime, "csv/TankConfig.csv"));
		setnAtkValue(csvutil->getInt(nLine, enumTankAtkValue, "csv/TankConfig.csv"));
		setnSpeed(csvutil->getInt(nLine, enumTankSpeed, "csv/TankConfig.csv"));
		setName(csvutil->getValue(nLine, enumTankName, "csv/TankConfig.csv").asString());
		setfShowTime(fShowTime);
		setnScore(csvutil->getInt(nLine, enumTanknScore, "csv/TankConfig.csv"));
		m_stopSpeed = m_nSpeed;
		int BulletID = csvutil->getInt(nLine, enumTankBulletID, "csv/TankConfig.csv");
		m_BulletMgr = BulletManager::createWithID(this, BulletID);
		this->addChild(m_BulletMgr);

		auto Tank = Sprite::create(StringUtils::format("myhero/HeroTank_%d.png", ID));
		this->bindSprite(Tank);
		
		auto canon = TankCanon::createWithID(ID);
		this->addChild(canon);
		m_Tankcanon = canon;
		this->setPosition(pos);
		
		bindHpBar();

		bRet = true;
	} while (0);
	return bRet;
}

bool EnemyTank::initTowerCanonByID(int ID, Point pos)
{
	
	return true;
}


EnemyTank * EnemyTank::createTowerCanonByID(int ID, Point pos)
{
	EnemyTank* myEnemyTowerCanon = new EnemyTank();
	if (myEnemyTowerCanon && myEnemyTowerCanon->initTowerCanonByID(ID, pos))
	{
		myEnemyTowerCanon->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(myEnemyTowerCanon);
	}
	return myEnemyTowerCanon;
}





