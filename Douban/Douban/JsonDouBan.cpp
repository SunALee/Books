//file name:	JsonDouBan.cpp
//author:		leo
//create time:	2013-01-16 15:26:49
//last modify:	2013-01-18 10:42:55
//description:	source file for JsonDouBan.h

#include "StdAfx.h"
#include ".\jsondouban.h"
#include <shlwapi.h>
#include "StringUtil.h"

CJsonDouBan::CJsonDouBan(void)
{
}

CJsonDouBan::~CJsonDouBan(void)
{
}

bool CJsonDouBan::Parse( const CString &strJson, JSON_INFO &tJsonInfo )
{
	string strJ = (LPCTSTR)strJson;
	
	size_t index = 0;
	
	strJ = strJ.substr(1, strJ.length()-2);
	
	//查询 此次返回的图书数量
	strJ = strJ.substr(8);
	index = strJ.find(',');
	string strValue = strJ.substr(0, index);
	strJ = strJ.substr(index);

	tJsonInfo.m_nCount = atoi(strValue.c_str());

	//查询 所获结果在全部结果中的偏移值
	strJ = strJ.substr(9);
	index = strJ.find(',');
	strValue = strJ.substr(0, index);
	strJ = strJ.substr(index);
	tJsonInfo.m_nOffset = atoi(strValue.c_str());

	//查询 全部书目条数
	strJ = strJ.substr(9);
	index = strJ.find(',');
	strValue = strJ.substr(0, index);
	strJ = strJ.substr(index);
	tJsonInfo.m_nTotal = atoi(strValue.c_str());

	//如果没有获取到书目，则直接返回
	if (0 == tJsonInfo.m_nCount ||
		0 == tJsonInfo.m_nTotal)
	{
		return true;
	}

	//将表示书目的Json字符串按每本书分割到字符串数组中
	strJ = strJ.substr(11, strJ.length()-12);
	CStringArray sarrBooks;
	ApiSplitToArray(sarrBooks, strJ.c_str(), "\"rating\":", TRUE, 1);
	int iCount = sarrBooks.GetSize();
	if (0 == iCount)
	{
		return false;
	}
	
	for (int i=0; i<iCount; ++i)
	{
		BOOK book;
		if (GetBookInfo(sarrBooks.GetAt(i), book))
		{
			tJsonInfo.m_lsBooks.push_front(book);
		}
	}
	return true;
}

bool CJsonDouBan::GetBookInfo( const CString &strBook, BOOK &book )
{
	string strB = (LPCTSTR)strBook;
	CStringUtil strUtil;
	wstring wstrB = strUtil.utf82ws(strB);
	CString strTemp(wstrB.c_str());
	strB = (LPCTSTR)strTemp;

	//查询书目出版时间
	size_t index = strB.find("\"pubdate\":\"");
	if (-1 == index) return false;
	strB = strB.substr(index+11);
	index = strB.find("\",");
	book.m_strPubdate = strB.substr(0, index);
	strB = strB.substr(index+1);

	//查询书目的id
	index = strB.find("\"id\":\"");
	if (-1 == index) return false;
	strB = strB.substr(index+6);
	index = strB.find(",");
	string strValue = strB.substr(0, index);
	book.m_ulID = atol(strValue.c_str());
	strB = strB.substr(index+1);

	//查询书目的书名
	index = strB.find("\"title\":\"");
	if (-1 == index) return false;
	strB = strB.substr(index+9);
	index = strB.find("\",");
	book.m_strTitle = strB.substr(0, index);
	strB = strB.substr(index+1);

	//查询书目的出版社
	index = strB.find("\"publisher\":\"");
	if (-1 == index) return false;
	strB = strB.substr(index+13);
	index = strB.find("\",");
	book.m_strPublisher = strB.substr(0, index);
	strB = strB.substr(index+1);

	//查询书目的作者
	index = strB.find("\"author\":");
	if (-1 == index) return false;
	strB = strB.substr(index+9);
	index = strB.find(",\"summary\":");
	strValue = strB.substr(0, index);
	strValue = strValue.substr(2, strValue.length()-4);
	CStringArray sarrAuthor;
	ApiSplitToArray(sarrAuthor, strValue.c_str(), "\",\"", TRUE, 1);
	if (sarrAuthor.IsEmpty())
	{
		return false;
	}
	for (int i=0; i<sarrAuthor.GetCount(); ++i )
	{
		if (book.m_strAuthor.empty())
		{
			book.m_strAuthor = (LPCTSTR)sarrAuthor.GetAt(i);
		}
		else
		{
			book.m_strAuthor = book.m_strAuthor + ", " + (LPCTSTR)sarrAuthor.GetAt(i);
		}
	}
	strB = strB.substr(index+1);

	//查询书目的简介
	index = strB.find("\"summary\":\"");
	if (-1 == index) return false;
	strB = strB.substr(index+11);
	index = strB.rfind("\"}");
	if (index != -1)
	{
		book.m_strSummary = strB.substr(0, index);
	}
	else
	{
		book.m_strSummary = strB.substr(0);
	}
	Replace(book.m_strSummary, "\\n", "\r\n");
	Replace(book.m_strSummary, "\\\"", "\"");
	Replace(book.m_strSummary, "\\/", "/");
	strB = strB.substr(index+1);
	
	return true;
}

tBOOK::tBOOK()
{
	m_ulID = 0;
}
