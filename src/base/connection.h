#pragma once
#ifndef CONNECTION_H
#define CONNECTION_H


class Connection
{
public:
	Connection();

	static Connection* share();
	void init(unsigned int w,unsigned int h);

	void update();

private:
	static Connection *instance;
	float curTicks;
	float preTicks;
	bool isFirstFrame;
};

#endif // !CONNECTION_H
