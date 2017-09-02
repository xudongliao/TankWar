#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define Auto_Move_Interval 3.0f
class HeroTank;
class EnemyTank;
class TankBase;
class MoveController: public Node
{
public:
	MoveController();
	virtual ~MoveController();
public:
	CREATE_FUNC(MoveController);
	static MoveController* createWithTank(TankBase*);
	static MoveController* createWithEnemy(TankBase*);
	void setSpeedX(double nSpeed);
	void setSpeedY(double nSpeed);
	void changeDirection(float angle);
	TankBase* getMyTank();

private:
	double m_nSpeedX;
	double m_nSpeedY;
private:
	virtual bool init();
	virtual bool initWithTank(TankBase*);
	virtual bool initWithEnemy(TankBase*);

	virtual void update(float dt);
	virtual void updateEnemy(float dt);
	virtual void autoMove(float dt);
	MoveController* m_Controller;
	TankBase* m_Tank;

};

