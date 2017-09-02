#pragma  once
#include "cocos2d.h"

USING_NS_CC;

class Floatword : public Node
{
public:
	CREATE_FUNC(Floatword);
	virtual bool init();
public:
	void showWord(const char*, Point pos);
private:
	Label* m_textlab;
};



