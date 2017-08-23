#include "TankController.h"

TankController::TankController()
{
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

bool TankController::initTankCtrWithLevel(int nLevel , TMXTiledMap* map)
{
	
	m_Tank= HeroTank::createFromCsvFileByID(nLevel);
	addChild(m_Tank);	

	auto objGroup = map->getObjectGroup("HeroTank");
	ValueMap playPointmap = objGroup->getObject("HeroTank");
	float posX = playPointmap.at("x").asFloat();
	float posY = playPointmap.at("y").asFloat();
	m_Tank->setPosition(posX, posY);

	return true;
}
