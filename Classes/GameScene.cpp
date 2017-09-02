#include "GameScene.h"
#include "TankController.h"
#include "TankCanon.h"
#include "MoveController.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Joystick.h"
#include "HeroTank.h"
#include "GameDataLayer.h"
#include "GlobeDefine.h"
#include "GamePause.h"
#include "GameSelect.h"
#include "soundEngine.h"
#include "gvarible.h"
#define PI 3.1415926
GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene * GameScene::createSceneWithLevel(int nLevel)
{
	auto scene = Scene::create();
	auto layer = GameScene::createWithLevel(nLevel);
	scene->addChild(layer);
	return scene;
	log("Test,%d",1);
}

bool GameScene::initWithLevel(int nLevel)
{
	


	auto rootNode = CSLoader::createNode("GameLayer.csb");
	addChild(rootNode, 5);
	auto button_pause = (ui::Button*) rootNode->getChildByName("Button_1");
	auto button_return = (ui::Button*) rootNode->getChildByName("Button_2");
	auto button3 = (ui::Button*) rootNode->getChildByName("Button_3");
	auto position = button3->getPosition();
	static bool judgeNum = true;
	button3->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (judgeNum == true)
			{
				button3->loadTextures("setting.png", "setting.png");
				auto backMove = MoveTo::create(0.1f, Vec2(326.43f, position.y - 1.5f));
				auto volumeMove = MoveTo::create(0.05f, Vec2(226.43f, position.y - 2.5f));
				button_pause->runAction(backMove);
				button_return->runAction(volumeMove);
				judgeNum = false;
			}
			else
			{
				button3->loadTextures("setting2.png", "setting2.png");
				auto backMove = MoveTo::create(0.1f, Vec2(126.43f, position.y - 1.5));
				auto volumeMove = MoveTo::create(0.05f, Vec2(126.43f, position.y - 2.5));
				button_pause->runAction(backMove);
				button_return->runAction(volumeMove);
				judgeNum = true;
			}
		}
	});

	button_pause->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			//button_pause->loadTextures("resume.png", "resume.png");
			RenderTexture* Render = getrenderTexture();
			Director::getInstance()->pushScene(GamePause::createScene(Render, nLevel));
		}

	});
	button_return->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			soundEngine::StopBGMusic(NULL);
			Director::getInstance()->resume();
			Director::getInstance()->replaceScene(GameSelect::createScene());
		}
	});

	////////////////////////////////////////////////////
	m_nLevel = nLevel;
	loadConfig();
	loadController();
	initData();
	
	return true;

	
}

GameScene * GameScene::createWithLevel(int nLevel)
{
	GameScene* myScene = new GameScene();
	if (myScene && myScene->initWithLevel(nLevel))
	{
		myScene->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(myScene);
	}
	return myScene;
}

void GameScene::loadConfig()
{

	soundEngine::KindsOfBgm(BATTELBGM, (double)g_BGpercent / 100);

	auto MapScene = TMXTiledMap::create(
		StringUtils::format("map/MapLevel_%d.tmx", m_nLevel).c_str());

	addChild(MapScene,1);

	log("Test,%d", 2);

	m_tankCtr = TankController::creatTankCtrWithLevel(m_nLevel, MapScene);

	addChild(m_tankCtr, 3);

	log("Test,%d", 3);

	/*auto map = TMXTiledMap::create(
		StringUtils::format("map/MapLevel_%d_%d.tmx", m_nLevel, m_nLevel).c_str());
	addChild(map, 5);*/

}

void GameScene::loadController()
{
	m_moveCtr = MoveController::createWithTank(m_tankCtr->getMyTank());
	addChild(m_moveCtr);
	int nSpeed = m_tankCtr->getMyTank()->getnSpeed();
	auto joystick1= Joystick::create();
	joystick1->bindMoveCtr(m_moveCtr);
	addChild(joystick1,10,999);
	
	auto _listener = EventListenerCustom::create(JoystickEvent::EVENT_JOYSTICK, [=](EventCustom* event) {
		JoystickEvent* jsevent = static_cast<JoystickEvent*>(event->getUserData());	
		double angle = jsevent->mAnagle;
		m_moveCtr->changeDirection(angle);

	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, m_moveCtr);


	auto listenerX = EventListenerKeyboard::create();
	listenerX->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		double angle = 0;
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			angle = 179;
			m_moveCtr->changeDirection(angle);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			angle = 0;
			m_moveCtr->changeDirection(angle);
			break;
		}
	};

	listenerX->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		m_moveCtr->setSpeedX(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerX, m_moveCtr);


	auto listenerY = EventListenerKeyboard::create();
	listenerY->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		double angle = 0;
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			angle = 90;
			m_moveCtr->changeDirection(angle);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			angle = -90;
			m_moveCtr->changeDirection(angle);
			break;
		}
	};

	listenerY->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
	m_moveCtr->setSpeedY(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerY, m_moveCtr);


	auto joystick2 = CanonJoystick::create();
	joystick2->bindMoveCtr(m_moveCtr);
	addChild(joystick2, 10, 999);
	auto _listener2 = EventListenerCustom::create(CanonjoystickEvent::EVENT_JOYSTICK, [=](EventCustom* event) {
		CanonjoystickEvent* jsevent = static_cast<CanonjoystickEvent*>(event->getUserData());
		double angle = jsevent->mAnagle;
		int a = angle;
		log("%d",a);
		m_tankCtr->getMyTank()->getMyCanon()->getSprite()->setRotation(-angle + 90 - m_tankCtr->getMyTank()->getangle());
		m_moveCtr->getMyTank()->setAtk(angle , true);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener2, m_moveCtr);

	

	log("Test,%d", 4);




}

void GameScene::initData()
{
	auto DataScene = GameDataLayer::create();

	this->addChild(DataScene, 5, "Data");

	DataScene->setMyGameScene(this);

	DataScene->setnLevel(m_nLevel);
	int nEnemyNum = m_tankCtr->getNotToShowEnemyNum();
	int nLifeNum = 3;
	int nPointNum = 0;


	NOTIFY->postNotification("EnemyNumChange", (Ref*)nEnemyNum);
	NOTIFY->postNotification("LifeNumChange", (Ref*)nLifeNum);
	NOTIFY->postNotification("PointNumChange", (Ref*)nPointNum);
}
RenderTexture* GameScene::getrenderTexture() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。  
	//这里类似截图。 

	renderTexture->begin();
	Director::getInstance()->getRunningScene()->visit();
	renderTexture->end();
	return renderTexture;
	log("Test,%d", 5);
}
