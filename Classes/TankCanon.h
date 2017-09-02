#pragma once
#include "Entity.h"
class TankCanon : public Entity
{
public:
	TankCanon();
	virtual ~TankCanon();
public:
	static TankCanon* createWithID(int);
	virtual bool initWithID(int);
	
};
