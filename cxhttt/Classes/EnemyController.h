#pragma once
#include "cocos2d.h"
USING_NS_CC;
class EnemyController:public Node
{
public:
	EnemyController();
	virtual ~EnemyController();
public:
	static EnemyController* createEnemyControllerWithLevel(int nLevel);
	bool initEnControllerWithLevel(int nLevel);
};

