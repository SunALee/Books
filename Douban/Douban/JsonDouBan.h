#pragma once
#include "common.h"

typedef struct tBOOK
{
	unsigned long m_ulID;		
	string m_strTitle;			
	string m_strPublisher;		
	string m_strAuthor;			
	string m_strPubdate;		
	string m_strSummary;		
	tBOOK();
}BOOK, *PBOOK;

typedef struct tJASON_INFO
{
	int m_nCount;		
	int m_nTotal;		
	int m_nOffset;		
	list<BOOK> m_lsBooks;
}JSON_INFO, *PJSON_INFO;

class CJsonDouBan
{
public:
	CJsonDouBan(void);
	~CJsonDouBan(void);

	bool Parse(const CString &strJson, JSON_INFO &tJsonInfo);

private:
	
	bool GetBookInfo(const CString &strBook, BOOK &book);

private:
	CString m_strJson;
};
