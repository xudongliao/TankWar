#include "Floatword.h"

bool Floatword::init() {
	m_textlab = Label::createWithSystemFont("", "Arial", 20);
	m_textlab->setColor(Color3B(255, 0, 0));
	m_textlab->setAnchorPoint(Vec2(1, 0));
	m_textlab->setVisible(false);

	addChild(m_textlab);
	return true;
}

void Floatword::showWord(const char* text, Point pos)
{
	m_textlab->setString(text);
	m_textlab->setPosition(pos);
	m_textlab->setVisible(true);

	auto scaletobig = ScaleTo::create(0.3f, 2.5f, 2.5f);
	auto scaleSmall = ScaleTo::create(0.5f, 0.5f, 0.5f);

	auto callFunc = CallFunc::create([&]() {
		m_textlab->setVisible(false);
		m_textlab->removeFromParent();
	});

	auto actions = Sequence::create(scaletobig, scaleSmall, callFunc, NULL);
	m_textlab->runAction(actions);
}