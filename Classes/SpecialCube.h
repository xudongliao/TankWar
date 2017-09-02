#pragma once
#include "TankBase.h"
#include "EnumSpecialCubeType.h"
class SpecialCube : public TankBase
{
public:
	SpecialCube();
	virtual ~SpecialCube();
public:
	static SpecialCube* CreateCubeWithType(EnumSpecialCubeType, Point);
	bool initWithType(Point, EnumSpecialCubeType);
	void deleteCube(float dt);
	int m_CubeType;
	int getCubeType();
};

