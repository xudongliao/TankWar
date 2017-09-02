#include "cocostudio/CocoStudio.h"
#include "GameDataLayer.h"
#include "GlobeDefine.h"
#include "EnumEndType.h"
#include "ui/CocosGUI.h"
#include "GameOver.h"
#include "soundEngine.h"
#include "gvarible.h"

GameDataLayer::GameDataLayer()
{
	m_nPointNum = 0;
	m_nLifeNum = 0;
	m_nEnemyNum = 0;
}

GameDataLayer::~GameDataLayer() {
	NOTIFY->removeAllObservers(this);
}

bool GameDataLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto UI = CSLoader::createNode("Layer.csb");
	this->addChild(UI);
	m_EnemyLab = static_cast<ui::Text*>(UI->getChildByName("nEnemy"));
	m_LifeLab = static_cast<ui::Text*>(UI->getChildByName("nLife"));
	m_PointLab = static_cast<ui::Text*>(UI->getChildByName("nScore"));
	
	NOTIFY->addObserver(this,
		callfuncO_selector(GameDataLayer::recvRefreshEnemyNum),
		"EnemyNumChange", NULL);

	NOTIFY->addObserver(this,
		callfuncO_selector(GameDataLayer::recvRefreshLifeNum),
		"LifeNumChange", NULL);

	NOTIFY->addObserver(this,
		callfuncO_selector(GameDataLayer::recvRefreshPoint),
		"PointNumChange", NULL);

	NOTIFY->addObserver(this,
		callfuncO_selector(GameDataLayer::recvRefreshWinOrDie),
		"GameIsOver", NULL);


	return true;
}

void GameDataLayer::recvRefreshEnemyNum(Ref * pData)
{
	int nEnemyNum = (int)pData;
	m_nEnemyNum += nEnemyNum;
	m_EnemyLab->setString(StringUtils::toString(m_nEnemyNum));
	if (m_nEnemyNum == 0)
	{
		NOTIFY->postNotification("GameIsOver", (Ref*)GAMEWIN);
	}
}

void GameDataLayer::recvRefreshLifeNum(Ref * pData)
{
	int nLifeNum = (int)pData;
	m_nLifeNum += nLifeNum;
	m_LifeLab->setString(StringUtils::toString(m_nLifeNum));
	if (m_nLifeNum == 0)
	{
		NOTIFY->postNotification("GameIsOver", (Ref*)GAMEFAIL);
	}
}

void GameDataLayer::recvRefreshPoint(Ref * pData)
{
	int nScore = (int)pData;
	m_nPointNum += nScore;
	m_PointLab->setString(StringUtils::toString(m_nPointNum));
}

void GameDataLayer::recvRefreshWinOrDie(Ref * pData)
{
	int type= (int)pData;
	soundEngine::StopBGMusic(BATTELBGM);
	switch (EndType(type))
	{

	case GAMEWIN:
		Director::getInstance()->replaceScene(GameOver::createSceneWithLevel(GAMEWIN, m_nLevel, myScene));
		break;
	case GAMEFAIL:
		Director::getInstance()->replaceScene(GameOver::createSceneWithLevel(GAMEFAIL, m_nLevel, myScene));
		break;
	}
}

void GameDataLayer::setnLevel(int nLevel)
{
	m_nLevel = nLevel;
}

void GameDataLayer::setMyGameScene(GameScene * gameScene)
{
	myScene = gameScene;
}
