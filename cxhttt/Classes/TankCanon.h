#pragma once
#include "Entity.h"
class TankCanon : public Entity
{
public:
	TankCanon();
	virtual ~TankCanon();
public:
	CREATE_FUNC(TankCanon);
	virtual bool init();
	CC_SYNTHESIZE(double, m_angle, angle);
	void addAngle(double angle, bool isRotate);
};

