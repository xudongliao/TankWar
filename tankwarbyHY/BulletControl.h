#pragma once

#include "cocos2d.h"
#include "Tank.h"
#include "Bullet.h"
USING_NS_CC;
class BulletControl:
	public cocos2d::Layer
{
public:

	CREATE_FUNC(BulletControl);
	void createBullet(Tank* owner, float distance, int attackValue, Vec2 pos, BulletType bulletType) {
		auto bullet = Bullet::create(owner, distance, attackValue, pos, bulletType);
		this->addChild(bullet);
	}
};