#include "BulletControl.h"

void BulletControl::createBullet(HeroTank * owner, float distance, int attackValue, Vec2 pos, BulletType bulletType)
{
		auto bullet = Bullet::create(owner, distance, attackValue, pos, bulletType);
		this->addChild(bullet);
}
