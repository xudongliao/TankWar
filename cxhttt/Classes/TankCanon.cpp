#include "TankCanon.h"

TankCanon::TankCanon()
{
}

TankCanon::~TankCanon()
{
}

bool TankCanon::init()
{
	Sprite* border = Sprite::create("myhero/canon.png");
	this->bindSprte(border);
	return true;
}

void TankCanon::addAngle(double angle, bool isRotate)
{
	setangle(getangle() + angle);
	if (isRotate)
	{
		setRotation(m_angle);
	}
}


