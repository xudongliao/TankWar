#include "Tank.h"



Tank::Tank() {}
Tank::~Tank() {}

Tank * Tank::create(const std::string filename)
{
	Tank* tank = new Tank();
	if (tank && tank->initWithFile(filename)) {
		tank->autorelease();
		return tank;
	}
	CC_SAFE_DELETE(tank);
	return nullptr;
}

void Tank::hit(float delta)
{
	_lifeValue = _lifeValue - delta;
}
