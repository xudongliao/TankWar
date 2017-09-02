#include "settingScene.h"
#include "GlobleMusicDefine.h"
Scene * settingScene::createScene() {
	auto scene = Scene::create();
	auto layer = settingScene::create();
	scene->addChild(layer);
	return scene;
}

bool settingScene::init() {
	if (!LayerColor::initWithColor(Color4B(0,0,0,100))) {
		return false;
	}

	soundEngine::KindsOfBgm(SETTINGBGM, (double)g_BGpercent / 100);

	auto rootNode = CSLoader::createNode("MenuScene.csb");
	addChild(rootNode);

	m_button1 = (ui::Button*)rootNode->getChildByName("Button_1");
	m_button1->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			settingScene::menuCallBack();
		}
	});

	m_slider1 = (ui::Slider*)rootNode->getChildByName("Slider_3");
	m_slider1->setPercent(g_BGpercent);
	m_slider1->addEventListener(CC_CALLBACK_2(settingScene::SliderCallBack1, this));

	m_slider2 = (ui::Slider*)rootNode->getChildByName("Slider_3_0");
	m_slider2->setPercent(g_SEpercent);
	m_slider2->addEventListener(CC_CALLBACK_2(settingScene::SliderCallBack2, this));

	return true;
}

void settingScene::SliderCallBack1(Ref *pSender, Slider::EventType type) {

	int percent = m_slider1->getPercent();

	soundEngine::SetBGVolume(percent);

}

void settingScene::SliderCallBack2(Ref *pSender, Slider::EventType type) {

	int percent = m_slider2->getPercent();

	soundEngine::SetSEVolume(percent);

}

void settingScene::menuCallBack() {

	soundEngine::StopBGMusic(SETTINGBGM);
	soundEngine::KindsOfSE(E_MoveBack, (double)g_SEpercent / 100);

	Director::getInstance()->replaceScene(TransitionFadeUp::create(0.1f, GameOpen::createScene()));
}

	

