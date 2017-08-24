#include "MoveController.h"
#include "HeroTank.h"
MoveController::MoveController()
{
	m_nSpeedX = 0;
	m_nSpeedY = 0;
	m_Controller = NULL;
	m_Tank = NULL;
}

MoveController::~MoveController()
{
}

MoveController * MoveController::createWithTank(HeroTank *Tank)
{
	auto MoveCtr = new MoveController();
	if (MoveCtr && MoveCtr->initWithTank(Tank))
	{
		MoveCtr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(MoveCtr);
	}
	return MoveCtr;
}

bool MoveController::init()
{
	return true;
}

bool MoveController::initWithTank(HeroTank* Tank)
{
	m_Tank = Tank;
	this->scheduleUpdate();
	return true;
}

void MoveController::update(float dt)
{
	Point pos = m_Tank->getPosition();
	Size size = Director::getInstance()->getVisibleSize();
	Size TankSize = m_Tank->getContentSize();
	if ((pos.x + TankSize.width / 2 <= size.width || m_nSpeedX < 0)
		&& ((pos.x - TankSize.width / 2) >= 0)|| m_nSpeedX > 0)
	{
		pos.x += m_nSpeedX/2;
	}
	if ((pos.y +TankSize.height/2 <=size.height || m_nSpeedY < 0) 
		&&( m_nSpeedY > 0||pos.y -TankSize.height/2 >= 0 ))
	{
		pos.y += m_nSpeedY/2;
	}
	m_Tank->setPosition(pos.x, pos.y);
}

void MoveController::setSpeedX(double nSpeed)
{
	m_nSpeedX = nSpeed;
}

void MoveController::setSpeedY(double nSpeed)
{
	m_nSpeedY = nSpeed;
}


void MoveController::RegisterTouchEvent()
{
}
