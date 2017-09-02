#pragma once
#include "TankBase.h"
class TankCanon;
class EnemyTank:public TankBase
{
public:
	EnemyTank();
	virtual ~EnemyTank();
public:
	static EnemyTank* createFromCsvFileByID(int ID, float fShowTime, Point pos);
	bool initFromCsvFlieByID(int ID, float fShowTime, Point pos);	
	static EnemyTank* createTowerCanonByID(int ID, Point pos);
	bool initTowerCanonByID(int ID, Point pos);
	CC_SYNTHESIZE(bool, m_isShowUp, isShowUp);
	
};

