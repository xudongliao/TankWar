#include "EnumCreateTankWithLevel.h"
#include "TankController.h"
#include "MoveController.h"
#include "BulletManager.h"
#include "GlobeDefine.h"
#include "EnemyTank.h"
#include "TankBase.h"
#include "HomeBase.h"
#include "CsvUtil.h"
#include "BombM.h"

TankController::TankController()
{
	m_floatShowTimeCount = 0;
}

TankController::~TankController()
{
}

TankController * TankController::creatTankCtrWithLevel(int nLevel, TMXTiledMap* map)
{
	auto TankCtr = new TankController();
	if (TankCtr&&TankCtr->initTankCtrWithLevel(nLevel, map))
	{
		TankCtr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(TankCtr);
	}
	return TankCtr;
}

bool TankController::initTankCtrWithLevel(int nLevel, TMXTiledMap* map)
{
	CreateHeroTank(nLevel, map);
	CreateEnemyTank(nLevel, map);
	CreateHome(nLevel, map);
	CreateCube(Point(500, 500));
	
	m_BombMgr = BombM::create();
	this->addChild(m_BombMgr);
	this->scheduleUpdate();
	return true;
}



HeroTank * TankController::getMyTank()
{
	return m_Tank;
}

void TankController::CreateHeroTank(int nLevel, TMXTiledMap* map)
{

	int ID = nLevel;
	
	m_Tank = HeroTank::createFromCsvFileByID(ID);
	addChild(m_Tank);
	m_Tank->setTMXmap(map);
	auto objGroup = map->getObjectGroup("HeroTank");
	ValueMap playPointmap = objGroup->getObject("HeroTank");
	float posX = playPointmap.at("x").asFloat();
	float posY = playPointmap.at("y").asFloat();
	m_Tank->setPosition(Vec2(posX, posY));
}

void TankController::CreateEnemyTank(int nLevel, TMXTiledMap* map)
{
	std::string sEnemyTankConfPath = StringUtils::format(
		"csv/levelConf/CreateTank_level%d.plist", nLevel);

	ValueMap fileDataMap = FileUtils::getInstance()->getValueMapFromFile(sEnemyTankConfPath.c_str());

	int size = fileDataMap.size();
	for (int i = 1; i <= size; i++) {
		Value value = fileDataMap.at(StringUtils::toString(i));
		ValueMap data = value.asValueMap();

		int ID = i;
		int TankID = data["TankID"].asInt();
		float fShowTime = data["ShowTime"].asFloat();
		Point pos;
		pos.x = data["posX"].asInt();
		pos.y = data["posY"].asInt();

		auto myEnemy = EnemyTank::createFromCsvFileByID(TankID, fShowTime, pos);	
		
		myEnemy->setVisible(false);
		m_EnemyTankList.pushBack(myEnemy);
		m_NotShowTankEnemyList.pushBack(myEnemy);
		myEnemy->setTMXmap(map);
		this->addChild(myEnemy);
	}
}

void TankController::CreateHome(int nLevel, TMXTiledMap * map)
{
	m_Home = HomeBase::CreateWithLevel(nLevel);
	addChild(m_Home);
	m_Home->setTMXmap(map);
	auto objGroup = map->getObjectGroup("HomeBase");
	ValueMap HomePointmap = objGroup->getObject("Home");
	float posX = HomePointmap.at("x").asFloat();
	float posY = HomePointmap.at("y").asFloat();
	m_Home->setPosition(Vec2(posX, posY));
}

void TankController::CreateCube(Point pos)
{
	auto rand = RandomHelper();
	int type = rand.random_int(0, 5);
	auto myCube = SpecialCube::CreateCubeWithType((EnumSpecialCubeType)type, pos);
	this->addChild(myCube);
	m_SpecialCubeList.pushBack(myCube);
}





TankBase* TankController::isWithinAnyTank(Point pos)
{
	
	TankBase* myTank = NULL;
	Vector<TankBase*>Tanklist = m_AllTankList;
	if (m_Tank)
	Tanklist.pushBack(m_Tank);
	if (m_Home)
	Tanklist.pushBack(m_Home);
	for (auto Tank:Tanklist)
	{
	
		Size TankSize = Tank->getContentSize();
		Point Tankpos = Tank->getPosition();
		
		if (pos.x > Tankpos.x - TankSize.width /  2 && 
			pos.x < Tankpos.x + TankSize.width /  2 &&
			pos.y > Tankpos.y - TankSize.height / 2 &&
			pos.y < Tankpos.y + TankSize.height /2)
		{
			myTank = Tank;
		}
	}
	return myTank;
}

SpecialCube * TankController::isWithinAnyCube(Point pos)
{
	SpecialCube* myCube = NULL;
	for (auto Cube : m_SpecialCubeList)
	{
		Size cubeSize = Cube->getContentSize();
		Point cubePos = Cube->getPosition();

		if (pos.x > cubePos.x - cubeSize.width / 2 &&
			pos.x < cubePos.x + cubeSize.width / 2 &&
			pos.y > cubePos.y - cubeSize.height / 2 &&
			pos.y < cubePos.y + cubeSize.height / 2)
		{
			myCube = Cube;
		}
	}
	return myCube;
}



void TankController::update(float dt)
{
	for (auto Tank : m_AllTankList) {
		if (Tank->isDead())
		{
			m_AllTankList.eraseObject(Tank);
		}
	}

	int nNotShowEnemyCount = m_NotShowTankEnemyList.size();
	if (nNotShowEnemyCount > 0)
	{
		m_floatShowTimeCount += dt;
	}
	Vector<TankBase*> EnemyTankWantToDelete;
	for (auto Enemy : m_NotShowTankEnemyList) {
		if (m_floatShowTimeCount >= Enemy->getfShowTime())
		{
			EnemyTankWantToDelete.pushBack(Enemy);
			Enemy->setVisible(true);
			m_AllTankList.pushBack(Enemy);
			auto MoveCtr = MoveController::createWithEnemy(Enemy);
			Enemy->addChild(MoveCtr);
		}
		for (auto Enemy : EnemyTankWantToDelete) {
			m_NotShowTankEnemyList.eraseObject(Enemy);
		}
	}

	for (auto myCube : m_SpecialCubeList) {
		if (myCube->isDead())
		{
			deleteCube(myCube);
		}
	}

	for (auto Enemy : m_AllTankList) {
		Point EnemyPos = Enemy->getPosition();
		float Atkdistance = Enemy->getMyBulltCtr()->getMyAtkDistance();
		if (isCloseToHeroTank(EnemyPos,Atkdistance))
		{
			Enemy->autoAtk(m_Tank);
			Enemy->setStop(true);
		}
		else if (isCloseToHomeBase(EnemyPos, Atkdistance))
		{
			Enemy->autoAtk(m_Home);
			Enemy->setStop(true);
		}
		else {
			Enemy->autoAtk(NULL);
			Enemy->setStop(false);
		}
	}
}

void TankController::deleteCube(SpecialCube* myCube)
{
	myCube->setVisible(false);
	m_SpecialCubeList.eraseObject(myCube);
}

BombM * TankController::getMyBombMgr()
{
	return m_BombMgr;
}

bool TankController::isCloseToHeroTank(Point pos, float distance)
{
	if (pos.getDistance(m_Tank->getPosition()) < distance)
	{
		return true;
	}
	return false;
}

bool TankController::isCloseToHomeBase(Point pos, float distance)
{
	if (pos.getDistance(m_Home->getPosition())< distance)
	{
		return true;
	}
	return false;
}

int TankController::getNotToShowEnemyNum()
{
	int size = m_NotShowTankEnemyList.size();
	return size;
}

