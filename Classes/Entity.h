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
	void bindSprite(Sprite*);
	void hurtMe(int);
	bool isDead();
protected:
	virtual void onDead();
	virtual void onHurt(int);
	virtual void onBindSprite();
	Sprite* m_sprite;
	bool m_isDead;

	CC_SYNTHESIZE(int, m_nID, nID);
	CC_SYNTHESIZE(int, m_nHp, nHp);
	CC_SYNTHESIZE(int, m_nSpeed, nSpeed);
	CC_SYNTHESIZE(int, m_nAtkValue, nAtkValue);
	CC_SYNTHESIZE(int, m_nKind, kind);
	CC_SYNTHESIZE(float, m_fShowTime, fShowTime);
	CC_SYNTHESIZE(std::string, m_sName, sName);
	CC_SYNTHESIZE(float, m_fCoolDownTime, fCoolDownTime);
	CC_SYNTHESIZE(int, m_nScore, nScore);
};

