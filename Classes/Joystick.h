/*
 * Joystick.h
 *
 *  Created on: 2015-2-1
 *      Author: yong
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "cocos2d.h"
using namespace cocos2d;
class MoveController;

class CanonjoystickEvent : public Ref {
private:
	CanonjoystickEvent();

public:
	virtual ~CanonjoystickEvent();
	virtual bool init(); 
	CREATE_FUNC(CanonjoystickEvent);

public:
	static const std::string EVENT_JOYSTICK;
	double mAnagle;

	//	double mX;
	//	double mY;
};


class JoystickEvent: public Ref {
private:
	JoystickEvent();

public:
	virtual ~JoystickEvent();
	virtual bool init();CREATE_FUNC(JoystickEvent)
	;

public:
	static const std::string EVENT_JOYSTICK;
	double mAnagle;
	
//	double mX;
//	double mY;
};

class Joystick: public Layer {
private:
	Joystick();

protected:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

public:
	virtual ~Joystick();
	virtual bool init();
	CREATE_FUNC(Joystick);
	void bindMoveCtr(MoveController*);
private:
	Sprite* mJsBg;
	Sprite* mJsCenter;
	Vec2 mJsPos = Vec2(200, 200);
	MoveController* m_moveCtr;
};

class MoveController;
class CanonJoystick : public Layer {
private:
	CanonJoystick();

protected:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

public:
	virtual ~CanonJoystick();
	virtual bool init();
	CREATE_FUNC(CanonJoystick);
	void bindMoveCtr(MoveController*);
private:
	MoveController* m_moveCtr;
	Sprite* mJsBg;
	Sprite* mJsCenter;
	Vec2 mJsPos = Vec2(200, 200);
};

#endif /* JOYSTICK_H_ */
