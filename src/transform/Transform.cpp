#include "Transform.h"

wstring Transform::stringToWstring(const string &str)
{
	int len;
	int slength = (int)str.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

string Transform::WstringTostring(const wstring &wstr)
{
	int l = wstr.length();
	char * t = new char[l];
	int multiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), l, t, 0, NULL, NULL);
	int res = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), l, t, multiLen, NULL, NULL);
	if (res == 0)
	{
		return string("");
	}
	return string(t);
}
