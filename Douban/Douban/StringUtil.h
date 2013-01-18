//StringUtil.h: interface for the CStringUtil class.
//description:
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGUTIL_H__4A589631_6A5D_430B_9011_C1124826D58A__INCLUDED_)
#define AFX_STRINGUTIL_H__4A589631_6A5D_430B_9011_C1124826D58A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class CStringUtil  
{
public:
	CStringUtil();
	virtual ~CStringUtil();
	
	static string ws2s(const wstring& ws);
	static wstring s2ws(const string& s);
	static string ws2utf8(const wstring& ws);
	static wstring utf82ws(const string& s);
};

#endif // !defined(AFX_STRINGUTIL_H__4A589631_6A5D_430B_9011_C1124826D58A__INCLUDED_)
