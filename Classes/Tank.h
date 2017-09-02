#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Tank :
	public cocos2d::Sprite
{
public:
	Tank();
	~Tank();
public:
	static Tank* create(const std::string filename);
	CC_SYNTHESIZE(float, _lifeValue, lifeValue);
	void hit(float delta);
private:



};

