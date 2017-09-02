#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace ui;
#define DISTANCE 500

#define DISTANCE 500
USING_NS_CC;
using namespace ui;

class GameSelect :
	public cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameSelect);
private:
	void totalrunFunc();
	void judgeFunc(Vector<Button*> buttons, float distance);
	void slideFunc(Vector<Button*> buttons, float distance);
	void soundFunc();

private:
	Vec2 m_pos;
	Vec2 m_newPos;
	bool judgeNum = true;
	bool soundNum = true;
	Button* m_button1;
	Button* m_button2;
	Button* m_button3;
	Button* m_button4;
	Button* m_button5;
	Button* m_button6;
	Button* m_firstButton;
	Button* m_lastButton;
	float m_distance = DISTANCE;
	Vector<Button*> m_buttons;
};

