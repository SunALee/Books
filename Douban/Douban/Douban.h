#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CDoubanApp:
// �йش����ʵ�֣������ Douban.cpp
//

class CDoubanApp : public CWinApp
{
public:
	CDoubanApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDoubanApp theApp;
