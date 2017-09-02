#include "HeroTank.h"
#include "TankCanon.h"
#include "CsvUtil.h"
#include "EnumTankTypeConfig.h"
#include "BulletManager.h"
#include "GlobeDefine.h"
#include "soundEngine.h"
#include "TankController.h"
#include "BombM.h"
#include "gvarible.h"
HeroTank::HeroTank()
{
	
}

HeroTank::~HeroTank()
{
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
	return herotank;
}

bool HeroTank::initFromCsvFileByID(int ID)
{
	bool bRet = false;
	do 
	{
		ID = 0;
		auto csvutil = CsvUtil::getInstance();
		std::string sHeroID = StringUtils::format("%d", ID);
		int nLine = csvutil->findValueInWithLine(sHeroID.c_str(), enumTankID, "csv/TankConfig.csv");
		CC_BREAK_IF(nLine < 0);
		
		setnID(ID);
		setnHp(csvutil->getInt(nLine, enumTankHp, "csv/TankConfig.csv"));
		setfCoolDownTime(csvutil->getFloat(nLine, enumTankCoolDownTime, "csv/TankConfig.csv"));
		setnAtkValue(csvutil->getInt(nLine, enumTankAtkValue, "csv/TankConfig.csv"));
		setnSpeed(csvutil->getInt(nLine, enumTankSpeed, "csv/TankConfig.csv"));
		setsName(csvutil->getValue(nLine, enumTankName, "csv/TankConfig.csv").asString());
		setfShowTime(-999);
		m_stopSpeed = getnSpeed();
		int BulletID = csvutil->getInt(nLine, enumTankBulletID, "csv/TankConfig.csv");
		ID = 2;
		auto Tank = Sprite::create(StringUtils::format("myhero/HeroTank_%d.png", ID));
		this->bindSprite(Tank);
		
		auto canon = TankCanon::createWithID(ID);
		this->addChild(canon);
		m_Tankcanon = canon;
		canon->setPosition(this->getPosition());

		bindHpBar();

		m_BulletMgr = BulletManager::createWithID(this, BulletID);
		this->addChild(m_BulletMgr);

		bRet = true;
	} while (0);
	return bRet;
}

void HeroTank::onDead()
{
	this->setVisible(false);
	this->scheduleOnce([&](float dt) {this->setVisible(true);
	auto blink = Blink::create(0.3f,6); 
	this->runAction(blink); }, 0.5f, "Null");
	NOTIFY->postNotification("LifeNumChange", (Ref*)(-1));
	
	soundEngine::KindsOfSE("music/dead.mp3", (double)g_SEpercent / 100);
	((TankController*)this->getParent())->getMyBombMgr()->createBomb(kPlayerTankBomb, this->getPosition());

	auto objGroup = m_map->getObjectGroup("HeroTank");
	ValueMap playPointmap = objGroup->getObject("HeroTank");
	float posX = playPointmap.at("x").asFloat();
	float posY = playPointmap.at("y").asFloat();
	this->setPosition(Vec2(posX, posY));

	

	eatFirstAidBox();
}

