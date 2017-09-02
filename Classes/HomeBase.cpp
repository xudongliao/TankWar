#include "BombM.h"
#include "HomeBase.h"
#include "GlobeDefine.h"
#include "EnumEndType.h"
#include "TankController.h"
#include "soundEngine.h"
#include "gvarible.h"
HomeBase::HomeBase()
{
	m_fShowTime = 999;
}


HomeBase::~HomeBase()
{
}

HomeBase * HomeBase::CreateWithLevel(int nLevel)
{
	HomeBase* homebase = new HomeBase();
	if (homebase && homebase ->initWithLevel(nLevel))
	{
		homebase->autorelease();
	}
	else {
		CC_SAFE_DELETE(homebase);
	}
	return homebase;
}

bool HomeBase::initWithLevel(int nLevel)
{
	bool bRet = false;
	do 
	{
		int n = 1;
		auto Home = Sprite::create(StringUtils::format("Sprite/HomeBase/Home_%d.png", n));
		this->bindSprite(Home);

		this->setnHp(1000);

		bindHpBar();
		bRet = true;
	} while (0);
	return bRet;
}

void HomeBase::onDead()
{
	this->setVisible(false);
	auto myBombMgr = ((TankController*)this->getParent())->getMyBombMgr();
	myBombMgr->createBomb(kHomeBomb, this->getPosition());
	NOTIFY->postNotification("GameIsOver", (Ref*)GAMEFAIL);
	soundEngine::KindsOfSE("music/dead.mp3", (double)g_SEpercent / 100);
}

