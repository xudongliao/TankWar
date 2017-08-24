#include "HeroTank.h"
#include "TankCanon.h"
#include "CsvUtil.h"
#include "EnumTankTypeConfig.h"
HeroTank::HeroTank()
{
	m_map = NULL;
	m_Tankcanon = NULL;
}

HeroTank::~HeroTank()
{
}


bool HeroTank::init()
{
	auto Tank = Sprite::create("myhero/HeroTank.png");
	this->bindSprte(Tank);
	auto canon = TankCanon::create();
	this->addChild(canon);
	m_Tankcanon = canon;
	return true;
}

HeroTank * HeroTank::createFromCsvFileByID(int ID)
{
	HeroTank* herotank = new HeroTank();
	if (herotank && herotank->initFromCsvFileByID(ID))
	{
		herotank->autorelease();
	}
	else {
		CC_SAFE_DELETE(herotank);
	}
	herotank->setScale(0.2);
	return herotank;
}

bool HeroTank::initFromCsvFileByID(int ID)
{
	bool bRet = false;
	do 
	{
		auto Tank = Sprite::create("myhero/HeroTank.png");
		this->bindSprte(Tank);
		auto canon = TankCanon::create();
		this->addChild(canon);
		m_Tankcanon = canon;

		auto csvutil = CsvUtil::getInstance();
		std::string sHeroID = StringUtils::format("%d", ID);
		int nLine = csvutil->findValueInWithLine(sHeroID.c_str(), enumTankID, "csv/HeroTank.csv");
		CC_BREAK_IF(nLine < 0);
		setnID(ID);
		setnHp(csvutil->getInt(nLine, enumTankHp, "csv/Hero.csv"));
		setnAtkValue(csvutil->getInt(nLine, enumTankAtkValue, "csv/HeroTank.csv"));
		setnSpeed(csvutil->getInt(nLine, enumTankSpeed, "csv/HeroTank.csv"));
		bRet = true;
	} while (0);
	return bRet;
}

void HeroTank::TankRotation(double angle)
{
	setRotation(angle);
	m_Tankcanon->setangle(angle);
}

/*void HeroTank::shoot()
{
	Vec2 bulletpos;
	bulletpos = this->getPosition();
	GameScene::getBulletController()->createBullet(this, 50.0f,10, bulletpos, SIMPLE);
}*/

void HeroTank::onDead()
{
}

void HeroTank::onHurt()
{
}


void HeroTank::atk() {

}