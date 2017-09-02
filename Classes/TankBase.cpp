#include "EnumMoveDirection.h"
#include "TankController.h"
#include "BulletManager.h"
#include "soundEngine.h"
#include "SpecialCube.h"
#include "GlobeDefine.h"
#include "Floatword.h"
#include "TankCanon.h"
#include "TankBase.h"
#include "BombM.h"
#include "gvarible.h"
#include "Bullet.h"

TankBase::TankBase()
{
	m_map = NULL;
	m_Tankcanon = NULL;
	m_isAtk = false;
	m_isCoolDown = false;
	m_Atkangle = 0;
	m_isUnAtkable = false;
}


TankBase::~TankBase()
{
}

void TankBase::TankRotation(double angle)
{
	this->getSprite()->setRotation(angle);
	this->getMyCanon()->setRotation(angle);
		this->setangle(angle);
}

TankCanon * TankBase::getMyCanon()
{
	return m_Tankcanon;
}


void TankBase::setTMXmap(TMXTiledMap * map)
{
	m_map = map;
	m_meta = m_map->getLayer("META");

	m_meta->setVisible(false);
}

bool TankBase::setTagPosition(float x, float y)
{
	Point dst1, dst2, dst3;
	Size Tanksize = this->getContentSize();
	int hfWidth = Tanksize.width / 2 - 7;
	int hfHeight = Tanksize.height / 2;

	switch ((int)m_Angle)
	{
	case 0:
		dst1 = Point(x - hfWidth, y + hfHeight);
		dst2 = Point(x, y + hfHeight);
		dst3 = Point(x + hfWidth, y + hfHeight);
		break;
	case 45:
		dst2 = Point(x + hfHeight / 1.4, y + hfHeight / 1.4);
		dst1 = Point(dst2.x - hfWidth / 1.4, y + hfWidth / 1.4);
		dst3 = Point(dst2.x + hfWidth / 1.4, y - hfWidth / 1.4);
		break;
	case 90:
		dst1 = Point(x + hfHeight, y + hfWidth);
		dst2 = Point(x + hfHeight, y);
		dst3 = Point(x + hfHeight, y - hfWidth);
		break;
	case 135:
		dst2 = Point(x + hfHeight / 1.4, y - hfHeight / 1.4);
		dst1 = Point(dst2.x + hfWidth / 1.4, y + hfWidth / 1.4);
		dst3 = Point(dst2.x - hfWidth / 1.4, y - hfWidth / 1.4);
		break;
	case 180:
		dst1 = Point(x + hfWidth, y - hfHeight);
		dst2 = Point(x, y - hfHeight);
		dst3 = Point(x - hfWidth, y - hfHeight);
		break;
	case 225:
		dst2 = Point(x - hfHeight / 1.4, y - hfHeight / 1.4);
		dst1 = Point(dst2.x - hfWidth / 1.4, y + hfWidth / 1.4);
		dst3 = Point(dst2.x + hfWidth / 1.4, y - hfWidth / 1.4);
		break;
	case 270:
		dst1 = Point(x - hfHeight, y + hfWidth);
		dst2 = Point(x - hfHeight, y);
		dst3 = Point(x - hfHeight, y - hfWidth);
		break;
	case -45:
		dst2 = Point(x - hfHeight / 1.4, y + hfHeight / 1.4);
		dst1 = Point(dst2.x + hfWidth / 1.4, y + hfWidth / 1.4);
		dst3 = Point(dst2.x - hfWidth / 1.4, y - hfWidth / 1.4);
		break;
	}
	Point pos[3] = { dst1,dst2,dst3 };

	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 3; i++) {
		if (pos[i].x < 10|| 
			pos[i].y < 10 || 
			pos[i].x > visibleSize.width -10 || 
			pos[i].y > visibleSize.height-10)
		{
			return false;
		}

		if (isTileValue("GoBack", pos[i], "true"))
		{
			return false;
		}
	}

	if (isTileValue("NotSee", Point(x, y), "true"))
	{
		this->setVisible(false);
	}
	if (isTileValue("ShowUp", Point(x,y), "true"))
	{
		this->setVisible(true);
	}
	
	for (int i = 0; i < 3; i++)
	{
		TankController* myCtr = (TankController*)this->getParent();
		if (myCtr->isWithinAnyTank(pos[i])
			!= this && myCtr->isWithinAnyTank(pos[i])
			!= NULL)
		{
			return false;
		}

	}
	if (m_fShowTime == -999)
	for (int i = 0; i < 3; i++)
	{
		TankController* myCtr = (TankController*)this->getParent();
		auto myCube = myCtr->isWithinAnyCube(pos[i]);
		if (myCube != NULL)
		{
			if (eatSpecialCube(myCube))
			{
				myCtr->deleteCube(myCube);
			}
		}
	}

	setPosition(Point(x, y));
	return true;
}

void TankBase::atk()
{
	if (!m_isAtk)
		return;
	if (m_isCoolDown)
		return;

	auto bullet = m_BulletMgr->getAnyUnUsedBullet();
	if (bullet != NULL)
	{
		Point pos = m_Tankcanon->getPosition();
		Size CanonSize = m_Tankcanon->getContentSize();
		pos.y = CanonSize.height /(float) 2 * cos(m_Atkangle) + pos.y;
		pos.x = CanonSize.height / (float)2 * sin(m_Atkangle) + pos.x;
		bullet->setPosition(pos);

		bullet->Move(m_Atkangle);
		m_isCoolDown = true;
		this->scheduleOnce(schedule_selector(TankBase::atkCoolDownEnd), m_fCoolDownTime/10.0f);
	}
}

void TankBase::autoAtk(TankBase* target)
{
	if (m_isCoolDown)
	{
		return;
	}
	double angle = 0;
	if (target != NULL)
	{
		Point Mypos = this->getPosition();
		Point targetPos = target->getPosition();
		double y = targetPos.y - Mypos.y;
		double x = targetPos.x - Mypos.x;
		angle = atan2(y, x) * 180 / PI;
	}
	else {
		auto rand = RandomHelper();
		angle = (double)rand.random_int(-179, 179);
	}
	m_Tankcanon->getSprite()->setRotation(-angle + 90 - getangle());
	setAtk(angle, true);
}

void TankBase::onDead()
{
	m_isDead = true;
	soundEngine::KindsOfSE("music/dead.mp3", (double)g_SEpercent / 100);
	Point pos = this->getPosition();
	TankController* myTankCtr = (TankController*)this->getParent();
	auto myBombMgr = (myTankCtr)->getMyBombMgr();
	myBombMgr->createBomb(kEnemyTankBomb, pos, m_MaxLife);
	NOTIFY->postNotification("PointNumChange", (Ref*)getnScore());
	NOTIFY->postNotification("EnemyNumChange", (Ref*)-1);
	auto rand = RandomHelper();
	int randIndex = rand.random_int(0, 100);
	if (randIndex < 50)
	{
		myTankCtr->CreateCube(this->getPosition());
	}
	this->removeFromParent();
	this->setVisible(false);
}

void TankBase::onHurt(int nHurtValue)
{
	this->m_hpBar->setPercent(m_nHp / (float)m_MaxLife * 100);
	auto floatword = Floatword::create();
	Point pos = this->getPosition();
	floatword->showWord(StringUtils::format("-%d", nHurtValue).c_str(),Point(0,0));
	addChild(floatword);
}

bool TankBase::isTileValue(const char * propValue, Point pos,const char* value)
{
	Point tiledPos = tileCordForPosition(pos);
	int tiledGid = m_meta->getTileGIDAt(tiledPos);
	if (0 != tiledGid)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid);
		ValueMap propertiesMap = properties.asValueMap();
		if (propertiesMap.find(propValue) != propertiesMap.end()) {
			Value prop = propertiesMap.at(propValue);
			if (0 == prop.asString().compare(value))
				return true;
		}
	}
	return false;
}

TMXTiledMap * TankBase::getMap()
{
	return m_map;
}

void TankBase::setAtk(double angle, bool isAtk)
{
	angle = (-angle + 90) / 180 * PI;
	m_Atkangle = angle;
	m_isAtk = isAtk;
}

void TankBase::bindHpBar()
{
	auto hpNode = CSLoader::createNode("HpBar.csb");
	m_hpBar = static_cast<ui::LoadingBar*>(hpNode->getChildByName("LoadingBar_1"));
	this->addChild(m_hpBar,9);

	float num = this->getContentSize().width / m_hpBar->getContentSize().width;

	m_hpBar->setScale(num);

	Point pos = m_hpBar->getPosition();
	pos.y += this->getContentSize().height / 2 +10;
	m_hpBar->setPosition(pos);
	
	m_hpBar->setPercent(100);
	m_MaxLife = m_nHp;
}

void TankBase::setStop(bool isStoped)
{
	if (isStoped)
	{
		setnSpeed(0);
	}
	else
	{
		setnSpeed(m_stopSpeed);
	}
}

BulletManager * TankBase::getMyBulltCtr()
{
	return m_BulletMgr;
}

Point TankBase::tileCordForPosition(Point pos)
{
	Size a = m_map->getTileSize();
	int x = pos.x / m_map->getTileSize().width;
	int y = ((m_map->getMapSize().height* m_map->getTileSize().height) - pos.y) / m_map->getTileSize().height;
	return Point(x, y);
}

void TankBase::atkCoolDownEnd(float dt)
{
	m_isCoolDown = false;
}

bool TankBase::eatSpecialCube(SpecialCube* myCube)
{
	auto type = myCube->getCubeType();
	switch (type)
	{
	case enumRandomCube:
		eatRandom();
		break;
	case enumFirstAidBox:
		eatFirstAidBox();
		break;
	case enumDefenseCircle:
		if (m_isUnAtkable)
		{
			return false;
		}
		eatDefenseCircle();
		break;
	case enumBigBullet:
		eatBigBullet();
		break;
	case enumUpdate:
		if (m_stopSpeed != getnSpeed())
		{
			return false;
		}
		eatUpdate();
		break;
	case enumAddLife:
		eatAddLife();
		break;
	default:
		break;
	}
	return true;
}

void TankBase::eatFirstAidBox()
{
	this->setnHp(m_MaxLife);
	eatDefenseCircle(5);
	m_hpBar->setPercent(100);
}

void TankBase::eatDefenseCircle(float duration)
{
	setUnAtkable(true);
	auto myEffect = Sprite::create("Sprite/SpecialCube/SpecialEffect/Denfense.png");
	
	myEffect->scheduleOnce([&](float dt)
	{this->removeChildByName("Denfense");},
		duration,
		"Null");
	auto rotateBy = RotateBy::create(25.0f, -360, -360);
	auto repeat = RepeatForever::create(rotateBy);
	myEffect->runAction(repeat);
	this->addChild(myEffect, duration, "Denfense");
	this->scheduleOnce([&](float dt) 
	{this->setUnAtkable(false); },
	duration,
	"Denfense");
}

void TankBase::eatBigBullet()
{
	m_BulletMgr->changeRpg();
	this->scheduleOnce([&](float) {m_BulletMgr->changeRpg(1); }, 10.0f,"changeRpg");
}

void TankBase::eatUpdate()
{
	auto myEffect = Sprite::create("Sprite/SpecialCube/SpecialEffect/Update.png");

	myEffect->scheduleOnce([&](float dt)
	{this->removeChildByName("Update"); },
		10.0f,
		"Null");
	

	auto rotateBy = RotateBy::create(10.0f, 360, 360);
	auto repeat = RepeatForever::create(rotateBy);
	myEffect->runAction(repeat);
	this->addChild(myEffect, 10,"Update");

	
	setnSpeed(getnSpeed() + 5);
	this->scheduleOnce([&](float dt)
	{this->setnSpeed(getnSpeed()-5); },
		10.0f,
		"Null");
	
}

void TankBase::eatAddLife()
{
	NOTIFY->postNotification("LifeNumChange", (Ref*)1);
}

void TankBase::eatRandom()
{
	NOTIFY->postNotification("PointNumChange", (Ref*)300);
}

void TankBase::changeBack(float dt)
{
	m_BulletMgr->changeRpg(1);
}
