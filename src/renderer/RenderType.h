#pragma once
#ifndef RENDERTYPE_H
#define RENDERTYPE_H

namespace RenderType {
	enum BufferType
	{
		Indices,
		Vertices
	};

	enum TexType
	{
		Tex2D,
		TexCube
	};

	enum Fuction
	{
		DepthTest,
		Blend
	};

	enum DrawType
	{
		TRI,
		TRI_STRIP
	};

	enum DepthTestFuc
	{
		less,
		lessOrQua
	};
}
#endif // !RENDERTYPE_H
