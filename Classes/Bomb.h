#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum BombType			// 爆炸类型 
{
	kPlayerTankBomb,	// 玩家坦克爆炸 
	kEnemyTankBomb,		// 敌人坦克爆炸 
	kHomeBomb,	        // 大本营爆炸 
	kBulletBomb			// 子弹爆炸 
};

/* 爆炸类 */
class Bomb : public Sprite
{
public:
	Bomb();
	~Bomb();

	//创建爆炸,type 爆炸类型, score分数
	static Bomb* create(BombType type, int score);
	virtual bool init(BombType type, int score);
private:
	BombType _type;
	int _score;
};

