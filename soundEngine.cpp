#include "SoundEngine.h"

Scene * soundEngine::createScene() {
	auto scene = Scene::create();
	auto layer = soundEngine::create();
	scene->addChild(layer);
	return scene;
}

bool soundEngine::init() {
	if (!Layer::init()) {
		return false;
	}

	auto rootNode = CSLoader::createNode("MenuScene.csb");
	addChild(rootNode);

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backMusic.mp3", true);
	
	m_slider1 = (ui::Slider*)rootNode->getChildByName("Slider_3");
	m_slider1->addEventListener(CC_CALLBACK_2(soundEngine::SliderCallBack, this));

	return true;
}

void soundEngine::SliderCallBack(Ref *pSender, Slider::EventType type) {
	
	int percent = m_slider1->getPercent();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(((double)percent)/100);

}

void soundEngine::menuCallBack() {

	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
