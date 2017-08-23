#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"


USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

class soundEngine :public cocos2d::Layer
{

public:
	Slider* m_slider1;
	static Scene* createScene();
	virtual bool init();
	void menuCallBack();
	void SliderCallBack(Ref *pSender, Slider::EventType type);
	CREATE_FUNC(soundEngine);


public:
	static void playBulletBombEffect();
	void playTankBombEffect();
};

