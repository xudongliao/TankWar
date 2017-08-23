#pragma once
#include "cocos2d.h"
#include "Tank.h"
USING_NS_CC;
enum BulletType
{
	 SIMPLE, //一般子弹
	 STRENGTHENED, //加强子弹
};
class Bullet :
	public cocos2d::Sprite
{
public:
	CC_SYNTHESIZE(int, _distance, distance); 
	CC_SYNTHESIZE(float, _attackValue, attackValue);
	static Bullet* create(Tank* owner, float distance, int attackValue,Vec2 pos, BulletType bulletType); //创建子弹指针，确定其所有者，攻击距离，伤害值，子弹类型
	void move(Point destPos); //子弹移动的动作
	Vec2 setDirection(Point curPos);  //子弹移动的方向  获得一个点
	bool Bullet::init(Tank* owner, float distance, int attackValue,Vec2 pos, BulletType bulletType ); //初始化子弹
	
private:
	
	Tank* _owner;//子弹所属的坦克名字
	Vec2 _pos;
	bool _isReachBorder; //子弹是否到达边界
	bool _isReachObstacle; //子弹是否碰到障碍物
	bool _isCollideTank; //子弹是否碰到坦克
	bool _isBomb; //是否爆炸
	Vec2 _nextPos;//下一帧的位置
	Vec2 _bombPos;//子弹爆炸位置

private:
	void collideTank();//判断子弹是否和坦克相碰撞
	void reachBorder();//判断子弹是否到达边界
	void reachObstacle();//判断子弹是否和建筑物相碰
	void valid(); //判断子弹是否还有效
	
};

