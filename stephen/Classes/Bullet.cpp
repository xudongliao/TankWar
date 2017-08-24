#include "Bullet.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "soundEngine.h"
USING_NS_CC;

Bullet * Bullet::create(HeroTank * owner, float distance, int attackValue,Vec2 pos, BulletType bulletType )
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->init(owner, distance, attackValue, pos,bulletType)) {
		bullet->autorelease();
		return bullet;
	}
	else {
		delete bullet;
		bullet = NULL;
		return bullet;
	}
}

void Bullet::move(Point destPos)
{
	auto pos = this->getPosition();
	auto move = MoveBy::create(0.4, Point(pos.x + setDirection(pos).x, pos.y + setDirection(pos).y));
	_nextPos.x = pos.x + setDirection(pos).x;
	_nextPos.y = pos.y + setDirection(pos).y;
	if (_isReachBorder || _isReachObstacle || _isCollideTank == false) {
		this->runAction(move);
	}
	else {
		this ->setVisible(false);
		soundEngine::KindsOfSE(E_Bullet, g_SEpercent);
	}
}
bool Bullet::init(HeroTank* owner, float distance, int attackValue, Vec2 pos, BulletType bulletType) {
	bool flag = false;
	if (bulletType == SIMPLE) {
		this->initWithFile("bullet2.png");
		_owner = owner;
		_distance = distance;
		_attackValue = attackValue;
		this->setPosition(pos);
		flag = true;
	}
	else if (bulletType == STRENGTHENED) {
		this->initWithFile("bullet3.png");
		_owner = owner;
		_distance = distance;
		_attackValue = attackValue;
		this->setPosition(pos);
		flag = true;
	}
	return flag;
}

void Bullet::collideTank()
{
	Vector<HeroTank*> &tanks = GameScene::getTankController()->getTanks();
	HeroTank* playerTank = GameScene::getTankController()->getPlayerTank();
	for (auto tank : tanks)
	{
		//判断是否是玩家坦克子弹打到敌人坦克或敌人坦克子弹打到玩家坦克的情况 
		if ((_owner == playerTank && tank != playerTank) || (_owner != playerTank && tank == playerTank))
		{
			auto otherPos = tank->getPosition();
			if (_nextPos.x <= otherPos.x + GAME_SCENE_WIDTH && _position.x >= otherPos.x - GAME_SCENE_WIDTH &&
				_nextPos.y <= otherPos.y + GAME_SCENE_HEIGHT && _position.y >= otherPos.y - GAME_SCENE_HEIGHT)
			{
				this->_isCollideTank = true;
				tank->hurtMe(_attackValue);
				this->setVisible(false);
				_isBomb = true;
				break;
			}
		}
	}
}

void Bullet::reachBorder()
{
	if (_nextPos.x < 0 || _nextPos.x >=GAME_SCENE_WIDTH ||
		_nextPos.y <= 0 || _nextPos.y > GAME_SCENE_HEIGHT)
	{
		this->_isReachBorder = true;
		if (_owner == GameScene::getTankController()->getPlayerTank())
		{
			soundEngine::KindsOfSE(E_Bullet, g_SEpercent);
		}
		_isBomb = true;
		this->setVisible(false);
		if (_nextPos.x < 0)
		{
			_bombPos.x = 0;
		}
		else if (_nextPos.x > GAME_SCENE_WIDTH)
		{
			_bombPos.x = GAME_SCENE_WIDTH;
		}
		else
		{
			_bombPos.x = _nextPos.x;
		}
		if (_nextPos.y < 0)
		{
			_bombPos.y = 0;
		}
		else if (_nextPos.y > GAME_SCENE_HEIGHT)
		{
			_bombPos.y = GAME_SCENE_HEIGHT;
		}
		else
		{
			_bombPos.y = _nextPos.y;
		}
	}
}

void Bullet::valid()
{
	this->collideTank();
	this->reachBorder();
	//this->reachObstacle();
}


Vec2  Bullet::setDirection(Point curPos)
{
	Vec2 destPos;
	int distance = Director::getInstance()->getVisibleSize().width;
	double angle = (destPos.y - curPos.y) / (destPos.x - curPos.x);
	if (curPos.x > destPos.x){
		destPos.x = curPos.x - distance;
	}
	else {
		destPos.x = curPos.x + distance;
	}

	if (curPos.y > destPos.y){
		destPos.y = curPos.y - distance / angle;
	}
	else {
		destPos.y = curPos.y + distance / angle;
	}
	return destPos;
}



