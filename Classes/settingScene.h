#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameOpenScene.h"
#include "soundEngine.h"



USING_NS_CC;
using namespace ui;

class settingScene :public cocos2d::LayerColor
{

public:
	Slider* m_slider1;
	Slider* m_slider2;
	Button* m_button1;
	static Scene* createScene();
	virtual bool init();
	void menuCallBack();
	void SliderCallBack1(Ref *pSender, Slider::EventType type);
	void SliderCallBack2(Ref *pSender, Slider::EventType type);
	CREATE_FUNC(settingScene);
};