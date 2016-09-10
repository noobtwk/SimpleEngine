#pragma once
#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include"vec2.h"

class Node;

class EventListener
{
public:
	EventListener();
	~EventListener() ;

	virtual bool onkeyPress(int keycode);
	virtual bool onkeyRelease(int keycode);
	virtual bool onMousePress(int button,vec2 pos);
	virtual bool onMouseMove(vec2 pos);
	virtual bool onMouseRelease(int button ,vec2 pos);

	int getFixedPiority() const;
	void setFiexdPiority(int piority);
	void setIsSwallow(bool isSwallow);


private:
	int fixedPiority;
	bool swallow;
};

#endif // !EVENT_H
