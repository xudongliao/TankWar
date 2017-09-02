#include "SpecialCube.h"
#include "TankBase.h"


SpecialCube::SpecialCube()
{
	m_isDead = false;
}


SpecialCube::~SpecialCube()
{
}

SpecialCube * SpecialCube::CreateCubeWithType(EnumSpecialCubeType type , Point pos)
{
	auto myCube = new SpecialCube;
	if (myCube && myCube->initWithType(pos, type))
	{
		myCube->autorelease();
	}
	else {
		CC_SAFE_DELETE(myCube);
	}
	return myCube;
}

bool SpecialCube::initWithType(Point pos , EnumSpecialCubeType type)
{
	bool bRet = false;
	do 
	{
		Sprite* myCube = NULL;
		m_CubeType = type;
		switch (type)
		{
		case enumRandomCube:
			myCube = Sprite::create("Sprite/SpecialCube/GoldBox.png");
			break;
		case enumFirstAidBox:
			myCube = Sprite::create("Sprite/SpecialCube/FirstAidBox.png");
			break;
		case enumDefenseCircle:
			myCube = Sprite::create("Sprite/SpecialCube/Denfense.png");
			break;
		case enumBigBullet:
			myCube = Sprite::create("Sprite/SpecialCube/Rpg.png");
			break;
		case enumUpdate:
			myCube = Sprite::create("Sprite/SpecialCube/Update.png");
			break;
		case enumAddLife:
			myCube = Sprite::create("Sprite/SpecialCube/AddLife.png");
			break;
		default:
			break;
		}
		this->bindSprite(myCube);
		this->setPosition(pos);
		this->scheduleOnce(schedule_selector(SpecialCube::deleteCube), 10.0f);
		bRet = true;
	} while (0);
	return bRet;
}

void SpecialCube::deleteCube(float dt)
{
	m_isDead = true;
}

int SpecialCube::getCubeType()
{
	return m_CubeType;
}

