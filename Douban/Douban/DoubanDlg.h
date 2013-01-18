//file name:	DoubanDlg.h
//author:		leo
//create time:	2013-01-16 15:26:49
//last modify:	2013-01-18 10:41:58
//description:	主窗口类头文件

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "jsondouban.h"


// CDoubanDlg 对话框
class CDoubanDlg : public CDialog
{
// 构造
public:
	CDoubanDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DOUBAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// 用来设置检索类型：按关键字Or按标签
	CComboBox m_ComboType;
	// 保存输入信息
	CString m_strInput;
	// 显示获取结果
	CListCtrl m_ListResult;
	CString m_strJson;
	int m_nCount;
	int m_nType;
	afx_msg void OnBnClickedBtnSubmit();
private:
	void InitResultList();
public:
	int m_nTotal;
	int m_nOffset;
	int m_nPageNum;
	JSON_INFO m_tJson_info;
	afx_msg void OnStnClickedTextPrevious();
	afx_msg void OnStnClickedTextNext();
	// 书目摘要
	CString m_strSummary;
	HCURSOR m_cur;
	afx_msg void OnLvnItemchangedListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuitemCheck();
	afx_msg void OnNMRclickListResult(NMHDR *pNMHDR, LRESULT *pResult);
};
