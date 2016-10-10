#pragma once
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include<glew.h>

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	static FrameBuffer* create(int w, int h, int n,bool isDepth = true);

	void init(int w, int h, int n);

	void bindForRead();
	void bindForWrite();
	void bindColorBuffer();
	void bindDepthBuffer();

	void setReadBuffer(unsigned int i);

private:
	int width;
	int height;
	unsigned int fbo;
	unsigned int *gbuffer;
	unsigned int gPosition;
	unsigned int gColor;
	unsigned int gNormal;
	unsigned int depthMap;
	bool isDepth;
	int num;
};

#endif // !FRAMEBUFFER_H
