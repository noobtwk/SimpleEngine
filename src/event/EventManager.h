#pragma once
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include"EventListener.h"
#include<vector>
#include"EventListener.h"
#include<algorithm>
#include<deque>
#include"Node.h"
#include<unordered_map>

#define KEY_PRESS 0
#define KEY_RELEASE 1
#define MOUSE_PRESS 2
#define MOUSE_RELEASE 3
#define MOUSE_MOVE 4
#define	SCROLL 5
#define CHAR_INPUT 6

struct info {
	int keycode;
	int button;
	vec2 pos;
	int type;
	unsigned int c;
	int y;
};

class EventManager
{
public:
	EventManager();

	static EventManager * share();

	void addListener(EventListener* l);
	void addNodeListener(Node * node, EventListener *l);

	void handleOnkeyPress(int keycode);
	void handleOnkeyRelease(int keycode);
	void handleOnMousePress(int bottom,vec2 pos);
	void handleOnMouseMove(vec2 pos);
	void handleOnMouseRelease(int bottom,vec2 pos);
	void handleOnScroll(int x, int y);
	void handleOnCharInput(unsigned int c);

	void use();

	static bool sortByPiority(EventListener *a,EventListener *b);
	void sortFixedListener();
	static bool sortByNodePiority(EventListener * a, EventListener *b);
	void sortNodeListener();
	void visit(Node * n);

private:
	void useKeyPress(int keycode);
	void useKeyRelease(int keycode);
	void useMousePress(int button, vec2 p);
	void useMouseRelease(int button, vec2 p);
	void useMouseMove(vec2 p);
	void useScroll(int y);
	void useCharInput(unsigned int c);

private:
	static EventManager * instance;
	std::vector<EventListener*> eventList;
	std::deque<info> eventDeque;
	std::deque<EventListener*> nodeListener;
	std::unordered_map<Node*, EventListener*> nodeListMap;

};

#endif // !EVENTMANAGER_H
