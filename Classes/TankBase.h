#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Entity.h"
USING_NS_CC;
#define PI 3.1415926

class BulletManager;
class TankCanon;
class SpecialCube;
class TankBase	:	public Entity
{
public:
	TankBase();
	virtual ~TankBase();
public:
	void TankRotation(double);
	TankCanon* getMyCanon();
	void setTMXmap(TMXTiledMap*);
	virtual bool setTagPosition(float x, float y);
	void atk();
	void autoAtk(TankBase*);
	bool isTileValue(const char*, Point, const char*);
	TMXTiledMap* getMap();
	void setAtk(double angle, bool isAtk);
	void bindHpBar();
	void setStop(bool);
	BulletManager* getMyBulltCtr();
protected:
	TankCanon* m_Tankcanon;
	void onDead() override;
	void onHurt(int ) override;
	TMXTiledMap* m_map;
	TMXLayer* m_meta;
	ui::LoadingBar*m_hpBar;
	int m_MaxLife;
	int m_stopSpeed;
	float m_biCoolDown;

	CC_SYNTHESIZE(int, m_nScore, nScore);
	CC_SYNTHESIZE(double, m_Angle, angle);
	CC_SYNTHESIZE(double, m_Atkangle, Atkangle);
	CC_SYNTHESIZE(double, m_isUnAtkable, UnAtkable);

	Point tileCordForPosition(Point pos);
	BulletManager* m_BulletMgr;
	bool m_isCoolDown;
	void atkCoolDownEnd(float);
	bool m_isAtk;
protected:
	
	bool eatSpecialCube(SpecialCube*);
	void eatFirstAidBox();
	void eatDefenseCircle(float duration = 10);
	void eatBigBullet();
	void eatUpdate();
	void eatAddLife();
	void eatRandom();
	void changeBack(float dt);
};

