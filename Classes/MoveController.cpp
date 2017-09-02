#include "MoveController.h"
#include "HeroTank.h"
#include "EnumMoveDirection.h"
#include "EnemyTank.h"
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

MoveController * MoveController::createWithTank(TankBase *Tank)
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

MoveController * MoveController::createWithEnemy(TankBase *myEnemy)
{
	auto EneMoveCtr = new MoveController();
	if (EneMoveCtr && EneMoveCtr->initWithEnemy(myEnemy))
	{
		EneMoveCtr->autorelease();
	}
	else {
		CC_SAFE_DELETE(EneMoveCtr);
	}
	return EneMoveCtr;
}

bool MoveController::init()
{
	return true;
}

bool MoveController::initWithTank(TankBase* Tank)
{
	m_Tank = Tank;
	this->scheduleUpdate();
	return true;
}

bool MoveController::initWithEnemy(TankBase * myEnemy)
{
	m_Tank = myEnemy;
	this->schedule(schedule_selector(MoveController::updateEnemy));
	autoMove(2.0f);
	this->schedule(schedule_selector(MoveController::autoMove),5.0f);
	return true;
}

void MoveController::update(float dt)
{
	Point pos = m_Tank->getPosition();
		pos.x += m_nSpeedX;
		pos.y += m_nSpeedY;
	m_Tank->setTagPosition(pos.x, pos.y);
	m_Tank->atk();
}

void MoveController::updateEnemy(float dt)
{
	Point pos = m_Tank->getPosition();
	pos.x += m_nSpeedX;
	pos.y += m_nSpeedY;
	if (!m_Tank->setTagPosition(pos.x, pos.y))
	{
		this->autoMove(dt);
	}
	m_Tank->atk();
}

void MoveController::autoMove(float dt)
{
	auto rand = RandomHelper();
	int randIndex = rand.random_int(-179, 179);
	changeDirection(randIndex);
}

void MoveController::setSpeedX(double nSpeed)
{
	m_nSpeedX = nSpeed;
}

void MoveController::setSpeedY(double nSpeed)
{
	m_nSpeedY = nSpeed;
}

void MoveController::changeDirection(float angle)
{
	int nSpeed = this->m_Tank->getnSpeed();
	switch ((int)(angle / 30))
	{
	case 0:
		this->setSpeedX(nSpeed);
		this->setSpeedY(0);
		m_Tank->TankRotation(90);
		break;

	case 1:
		this->setSpeedX(nSpeed / 1.4);
		this->setSpeedY(nSpeed / 1.4);
		m_Tank->TankRotation(45);
		break;
	case 2:
	case 3:
		this->setSpeedX(0);
		this->setSpeedY(nSpeed);
		m_Tank->TankRotation(0);
		break;

	case 4:
		this->setSpeedX(-nSpeed / 1.4);
		this->setSpeedY(nSpeed / 1.4);
		m_Tank->TankRotation(-45);
		break;
	case -1:
		this->setSpeedX(nSpeed / 1.4);
		this->setSpeedY(-nSpeed / 1.4);
		m_Tank->TankRotation(135);
		break;
	case-2:
	case-3:
		this->setSpeedX(0);
		this->setSpeedY(-nSpeed);
		m_Tank->TankRotation(180);
		break;
	case -4:
		this->setSpeedX(-nSpeed / 1.4);
		this->setSpeedY(-nSpeed / 1.4);
		m_Tank->TankRotation(225);
		break;
	case 5:
	case -5:
		this->setSpeedX(-nSpeed / 1.4);
		this->setSpeedY(0);
		m_Tank->TankRotation(270);
		break;
	}
}

TankBase * MoveController::getMyTank()
{
	return m_Tank;
}


