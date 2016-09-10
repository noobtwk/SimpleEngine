#ifndef TRANSFORM_H
#define TRAMSFPRM_H
#include<string>
#include <stdarg.h>
#include <windows.h>
using namespace std;

class Transform
{
public:
	static wstring stringToWstring(const string &str);
	static string WstringTostring(const wstring &wstr);
};
#endif // !TRANSFORM_H
