#include "GameSelect.h"
#include "GameOpenScene.h"
#include "GameScene.h"
#include "soundEngine.h"

Scene * GameSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSelect::create();
	scene->addChild(layer);
	return scene;
}

bool GameSelect::init()
{

	soundEngine::KindsOfBgm(SETTINGBGM, g_BGpercent);

	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("SelectScene.csb");
	addChild(rootNode);
	m_button1 = (Button*)rootNode->getChildByName("Button_1");
	m_button2 = (Button*)rootNode->getChildByName("Button_2");
	m_button3 = (Button*)rootNode->getChildByName("Button_3");
	m_button4 = (Button*)rootNode->getChildByName("Button_4");
	m_button5 = (Button*)rootNode->getChildByName("Button_5");
	m_button6 = (Button*)rootNode->getChildByName("Button_6");

	m_buttons.pushBack(m_button1);
	m_buttons.pushBack(m_button2);
	m_buttons.pushBack(m_button3);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		auto pos = touch->getPreviousLocationInView();
		m_pos = Director::getInstance()->convertToGL(pos);
		return true;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		auto newPos = touch->getPreviousLocationInView();
		m_newPos = Director::getInstance()->convertToGL(newPos);

		totalrunFunc();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	m_button1->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		Point point = m_button1->getPosition();
		float moveDistance = (Director::getInstance()->getVisibleSize().width / 2) - point.x;
		if (type == Widget::TouchEventType::ENDED)
		{
			m_firstButton = m_button1;
			m_lastButton = NULL;

			if (moveDistance <= -100 || moveDistance >= 100)
			{
				for (auto button : m_buttons)
				{
					auto moveby = MoveBy::create(0.3f, Vec2(moveDistance, 0));
					auto scaleresume = ScaleTo::create(0.3f, 2.5f, 2.5f);
					auto spw = Spawn::create(moveby, scaleresume, NULL);
					button->runAction(spw);
				}
				auto scaleto = ScaleTo::create(0.3f, 3.0f, 3.0f);
				auto runNull = MoveBy::create(0.05f, Vec2(0, 0));

				auto callbackFunc = [=]()
				{
					soundEngine::StopBGMusic(NULL);
					Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(1)));
				};

				CallFunc* callFunc = CallFunc::create(callbackFunc);

				Action* actions = Sequence::create(scaleto, runNull, callFunc, NULL);

				m_button1->runAction(actions);
			}
			else {
				soundEngine::StopBGMusic(NULL);
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(1)));
			}
		}
	});

	m_button2->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		Point point = m_button2->getPosition();
		float moveDistance = (Director::getInstance()->getVisibleSize().width / 2) - point.x;
		if (type == Widget::TouchEventType::ENDED)
		{
			m_firstButton = NULL;
			m_lastButton = NULL;

			if (moveDistance <= -100 || moveDistance >= 100)
			{
				for (auto button : m_buttons)
				{
					auto moveby = MoveBy::create(0.3f, Vec2(moveDistance, 0));
					auto scaleresume = ScaleTo::create(0.3f, 2.5f, 2.5f);
					auto spw = Spawn::create(moveby, scaleresume, NULL);
					button->runAction(spw);
				}
				auto scaleto = ScaleTo::create(0.3f, 3.0f, 3.0f);
				auto runNull = MoveBy::create(0.05f, Vec2(0, 0));

				auto callbackFunc = [=]()
				{
					soundEngine::StopBGMusic(NULL);
					Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(2)));
				};

				CallFunc* callFunc = CallFunc::create(callbackFunc);

				Action* actions = Sequence::create(scaleto, runNull, callFunc, NULL);

				m_button2->runAction(actions);
			}
			else
			{
				soundEngine::StopBGMusic(NULL);
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(2)));
			}
		}
	});

	m_button3->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		Point point = m_button3->getPosition();
		float moveDistance = (Director::getInstance()->getVisibleSize().width / 2) - point.x;
		if (type == Widget::TouchEventType::ENDED)
		{
			m_firstButton = NULL;
			m_lastButton = m_button3;

			if (moveDistance <= -100 || moveDistance >= 100)
			{
				for (auto button : m_buttons)
				{
					auto moveby = MoveBy::create(0.3f, Vec2(moveDistance, 0));
					auto scaleresume = ScaleTo::create(0.3f, 2.5f, 2.5f);
					auto spw = Spawn::create(moveby, scaleresume, NULL);
					button->runAction(spw);
				}
				auto scaleto = ScaleTo::create(0.3f, 3.0f, 3.0f);
				auto runNull = MoveBy::create(0.05f, Vec2(0, 0));

				auto callbackFunc = [=]()
				{
					Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(3)));
				};

				CallFunc* callFunc = CallFunc::create(callbackFunc);

				Action* actions = Sequence::create(scaleto, runNull, callFunc, NULL);

				m_button3->runAction(actions);
			}
			else
			{
				soundEngine::StopBGMusic(NULL);
				Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::createSceneWithLevel(3)));
			}	
		}
	});

	judgeFunc(m_buttons, 0);

	auto position = m_button4->getPosition();
	m_button4->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			soundEngine::StopBGMusic(NULL);
			Director::getInstance()->replaceScene(TransitionFadeUp::create(0.5f, GameOpen::createScene()));
		}
	});

	m_button5->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (judgeNum == true)
			{
				m_button5->loadTextures("setting.png", "setting.png");
				auto backMove = MoveTo::create(0.1f, Vec2(300, position.y - 2.5l));
				auto volumeMove = MoveTo::create(0.05f, Vec2(200, position.y));
				m_button4->runAction(backMove);
				m_button6->runAction(volumeMove);
				judgeNum = false;
			}
			else
			{
				m_button5->loadTextures("setting2.png", "setting2.png");
				auto backMove = MoveTo::create(0.1f, Vec2(100, position.y));
				auto volumeMove = MoveTo::create(0.05f, Vec2(100, position.y));
				m_button4->runAction(backMove);
				m_button6->runAction(volumeMove);
				judgeNum = true;
			}
		}
	});

	m_button6->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			soundFunc();
		}
	});

	return true;
}



void GameSelect::totalrunFunc()
{
	m_distance = DISTANCE;

	if (m_pos.x > m_newPos.x) // 向左移动
	{
		m_firstButton = NULL;

		if (m_lastButton != m_button3)
		{
			m_distance = -m_distance;
			slideFunc(m_buttons, m_distance);
			judgeFunc(m_buttons, m_distance);
		}
	}
	else if (m_pos.x == m_newPos.x);
	else if (m_pos.x < m_newPos.x) //向右移动
	{
		m_lastButton = NULL;

		if (m_firstButton != m_button1)
		{
			slideFunc(m_buttons, m_distance);
			judgeFunc(m_buttons, m_distance);
		}
	}
}

void GameSelect::judgeFunc(Vector<Button*> buttons, float distance)
{
	for (auto button : buttons)
	{
		Vec2 pos = button->getPosition();
		Size size = Director::getInstance()->getVisibleSize();

		if ((pos.x + distance - size.width / 2) < 200 && -200 < (pos.x + distance - size.width / 2))
		{
			auto scale1 = ScaleTo::create(0.3f, 3.0f, 3.0f);
			button->runAction(scale1);

			if (button == m_button1)
				m_firstButton = m_button1;
			else if (button == m_button3)
				m_lastButton = m_button3;
		}
		else
		{
			auto scale2 = ScaleTo::create(0.3f, 2.5f, 2.5f);
			button->runAction(scale2);
		}
	}
}

void GameSelect::slideFunc(Vector<Button*> buttons, float distance)
{
	for (auto button : buttons)
	{
		Vec2 pos = button->getPosition();
		Vec2 newpos;
		newpos.x = pos.x + distance;
		newpos.y = pos.y;
		auto move = MoveTo::create(0.3f, newpos);
		button->runAction(move);
	}
}

void GameSelect::soundFunc()
{
	if (soundNum == true)
	{
		m_button6->loadTextures("volume2.png", "volume2.png");
		soundEngine::PauseBGMusic();
		soundNum = false;
	}
	else
	{
		m_button6->loadTextures("volume.png", "volume.png");
		soundEngine::ResumeBGMusic();
		soundNum = true;
	}

}

//void GameSelect::change(float dt)
//{
//	Director::getInstance()->replaceScene(TransitionFadeUp::create(0.1f, GameScene::createScene()));
//}