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
	virtual bool onScroll(int x, int y);
	virtual bool onCharInput(unsigned int c);

	int getFixedPiority() const;
	void setFiexdPiority(int piority);
	void setIsSwallow(bool isSwallow);
	bool isSwallow() const;

	void setLinkNode(Node * node);
	Node* getLinkNode()const;

private:
	int fixedPiority;
	bool swallow;
	Node * linkNode;
};

#endif // !EVENT_H
