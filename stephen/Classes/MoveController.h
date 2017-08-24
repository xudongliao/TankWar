#pragma once
#include "cocos2d.h"
USING_NS_CC;
class HeroTank;
class MoveController: public Node
{
public:
	MoveController();
	virtual ~MoveController();
public:
	CREATE_FUNC(MoveController);
	static MoveController* createWithTank(HeroTank*);
	virtual bool init();
	virtual bool initWithTank(HeroTank*);
	virtual void update(float dt);
	void setSpeedX(double nSpeed);
	void setSpeedY(double nSpeed);
private:
	double m_nSpeedX;
	double m_nSpeedY;
private:
	void RegisterTouchEvent();
	MoveController* m_Controller;
	HeroTank* m_Tank;
	
};

