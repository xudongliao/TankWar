#pragma once
#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;
class bombM;
class TankBase;
class Bullet :public Entity
{
public:
	static Bullet* create(int ID); //创建子弹指针，确定其所有者，攻击距离，伤害值，子弹类型
	bool init(int ID); //初始化子弹
	void Move(double angle);
	void Move(Point pos);
private:

	CC_SYNTHESIZE(float, m_fDistance, fDistance);
	CC_SYNTHESIZE(float, m_fAngle, fAngle);
	bool collideWithOthers();
	bool RPGcollideWithOthers();
	TankBase* m_Tank;//子弹所属的坦克
public:
	void setUsed(bool isUsed);
	bool isUsed();
	bool isArrive();
private:
	bool m_isUsed;
	bool m_isArrive;

};