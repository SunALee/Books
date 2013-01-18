#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <list>

#ifdef _DEBUG
#define	WRITE_LOG	true
#else
#define WRITE_LOG	false
#endif

#define SEARCH_KEY	0x0001
#define SEARCH_TAG	0x0002
#define SEARCH_ISBN	0x0002

using std::string;
using std::fstream;
using std::ios;
using std::list;
using std::wstring;

BOOL ApiGetHttpData(const string &strUrl, CString &strPageFile);

void ApiWriteLog(string strLog, bool bAppend=TRUE);

CString ApiGetDetailTime();

BOOL GetJSON(CString &strPageFile, CString strKey, int nType=SEARCH_KEY, int nStart=0);

int ApiSplitToArray(CStringArray &strArray, const CString &strInput, string strKey, BOOL bClear, int iNum);

int Replace(string &strValue, const string strCur, const string strNew);