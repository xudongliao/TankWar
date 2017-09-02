#include "TankCanon.h"

TankCanon::TankCanon()
{
}

TankCanon::~TankCanon()
{
}

TankCanon * TankCanon::createWithID(int ID)
{
	TankCanon* myCanon = new TankCanon();
	if (myCanon&& myCanon->initWithID(ID))
	{
		myCanon->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(myCanon);
	}
	return myCanon;
}

bool TankCanon::initWithID(int ID)
{
	Sprite* border = Sprite::create(StringUtils::format("myhero/canon_%d.png", ID));
	this->bindSprite(border);
	return true;
}






