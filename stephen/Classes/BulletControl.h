#pragma once

#include "cocos2d.h"
#include "HeroTank.h"
#include "Bullet.h"
USING_NS_CC;
class BulletControl:
	public cocos2d::Layer
{
public:

	CREATE_FUNC(BulletControl);
	void createBullet(HeroTank* owner, float distance, int attackValue, Vec2 pos, BulletType bulletType);
	
};

