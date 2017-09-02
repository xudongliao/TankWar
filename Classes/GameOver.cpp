#include "GameOver.h"
#include "GameScene.h"
#include "GameOpenScene.h"
#include "EnumEndType.h"
using namespace ui;
GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

Scene * GameOver::createSceneWithLevel(EndType endType, int nLevel, GameScene* myScene)
{
	auto scene = Scene::create();
	auto layer = GameOver::createWithLevel(endType, nLevel, myScene);
	scene->addChild(layer);
	return scene;
}

bool GameOver::initWithLevel(EndType endType, int nLevel, GameScene* gameScene)
{
	if (!LayerColor::initWithColor(Color4B((GLubyte)0, (GLubyte)0, (GLubyte)0, (GLubyte)70)))
		return false;
	
	if (endType == GAMEWIN) {
		auto rootNode1 = CSLoader::createNode("GameWin.csb");
		this->addChild(rootNode1);

		/*胜利场景的两个按钮*/
		auto button1 = (ui::Button*)rootNode1->getChildByName("Button_1");//返回主菜单
		button1->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				gameScene->removeAllChildrenWithCleanup(true);
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameOpen::createScene()));
			}
		});
		auto button2 = (ui::Button*)rootNode1->getChildByName("Button_2");//下一关
		button2->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				int level = nLevel;
				if (level != 3)
				{
					level += 1;
				}
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(level)));
			}
		});
	}
	else {
		auto rootNode2 = CSLoader::createNode("GameFail.csb");
		this->addChild(rootNode2);

		/*失败场景的两个按钮*/
		auto button3 = (ui::Button*)rootNode2->getChildByName("Button_1");//返回主菜单
		button3->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameOpen::createScene()));
			}
		});
		auto button4 = (ui::Button*)rootNode2->getChildByName("Button_2");//重新开始
		button4->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(nLevel)));
			}
		});
	}
	return true;
	
}

GameOver * GameOver::createWithLevel(EndType endType, int nLevel, GameScene* gameScene)
{
		GameOver*pRet = new GameOver(); 
		if (pRet && pRet->initWithLevel(endType, nLevel, gameScene))
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
}

void GameOver::setMyScene(GameScene *gameScene)
{
	m_gameScene = gameScene;
}
