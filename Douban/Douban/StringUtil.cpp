// StringUtil.cpp: implementation of the CStringUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Huweishen.h"
#include "StringUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringUtil::CStringUtil()
{

}

CStringUtil::~CStringUtil()
{

}

//宽字节转换为Unicode
string CStringUtil::ws2s(const wstring& ws)
{
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = WideCharToMultiByte(CP_ACP, 0, _Source, -1, NULL, 0, NULL, NULL);
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0x00, sizeof(char) * _Dsize);
	WideCharToMultiByte(CP_ACP, 0, _Source, -1, _Dest, _Dsize, NULL, NULL);
	string result = _Dest;
	delete []_Dest;
	return result;
}

//Unicode转换为宽字节
wstring CStringUtil::s2ws(const string& s)
{
	const char* _Source = s.c_str();
	size_t _Dsize = MultiByteToWideChar(CP_ACP, 0, _Source, -1, NULL, 0);
	wchar_t *_Dest = new wchar_t[_Dsize];
	memset(_Dest, 0x00, sizeof(wchar_t) * _Dsize);
	MultiByteToWideChar(CP_ACP, 0, _Source, -1, _Dest, _Dsize);
	wstring result = _Dest;
	delete []_Dest;
	return result;
}

//宽字节转换为UTF-8
string CStringUtil::ws2utf8(const wstring& ws)
{
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = WideCharToMultiByte(CP_UTF8, 0, _Source, -1, NULL, 0, NULL, NULL);
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0x00, sizeof(char) * _Dsize);
	WideCharToMultiByte(CP_UTF8, 0, _Source, -1, _Dest, _Dsize, NULL, NULL);
	string result = _Dest;
	delete []_Dest;
	return result;
}

//UTF-8转换为宽字节
wstring CStringUtil::utf82ws(const string& s)
{
	const char* _Source = s.c_str();
	size_t _Dsize = MultiByteToWideChar(CP_UTF8, 0, _Source, -1, NULL, 0);
	wchar_t *_Dest = new wchar_t[_Dsize];
	memset(_Dest, 0x00, sizeof(wchar_t) * _Dsize);
	MultiByteToWideChar(CP_UTF8, 0, _Source, -1, _Dest, _Dsize);
	wstring result = _Dest;
	delete []_Dest;
	return result;
}