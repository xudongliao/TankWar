#pragma  once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class GameScene;
class GameDataLayer:public Layer
{
public:
	GameDataLayer();
	virtual ~GameDataLayer();
public:
	CREATE_FUNC(GameDataLayer);
	virtual bool init();
public:
	void recvRefreshEnemyNum(Ref* pData);
	void recvRefreshLifeNum(Ref* pData);
	void recvRefreshPoint(Ref* pData);
	void recvRefreshWinOrDie(Ref* pData);
	void setnLevel(int nLevel);
	void setMyGameScene(GameScene*);
	int m_nEnemyNum;
	int m_nLifeNum;
	int m_nPointNum;
	int m_nLevel;
	GameScene* myScene;
	ui::Text* m_EnemyLab;
	ui::Text* m_LifeLab;
	ui::Text* m_PointLab;
};