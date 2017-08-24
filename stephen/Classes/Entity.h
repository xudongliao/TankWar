#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity : public Node
{
public:
	Entity();
	virtual ~Entity();
public:
	Sprite* getSprite();
	void bindSprte(Sprite*);
	void hurtMe(int);
	bool isDead();
protected:
	virtual void onDead();
	virtual void onHurt(int);
	virtual void onBindSprite();
private:
	Sprite* m_sprite;
	bool m_isDead;
	
	CC_SYNTHESIZE(int, m_nID, nID);
	CC_SYNTHESIZE(int, m_nHp, nHp);
	CC_SYNTHESIZE(int, m_nSpeed, nSpeed);
	CC_SYNTHESIZE(int, m_nAtkValue, nAtkValue);
	CC_SYNTHESIZE(std::string, m_sName, sName);
};

