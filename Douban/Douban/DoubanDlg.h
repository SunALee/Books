//file name:	DoubanDlg.h
//author:		leo
//create time:	2013-01-16 15:26:49
//last modify:	2013-01-18 10:41:58
//description:	��������ͷ�ļ�

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "jsondouban.h"


// CDoubanDlg �Ի���
class CDoubanDlg : public CDialog
{
// ����
public:
	CDoubanDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DOUBAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// �������ü������ͣ����ؼ���Or����ǩ
	CComboBox m_ComboType;
	// ����������Ϣ
	CString m_strInput;
	// ��ʾ��ȡ���
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
	// ��ĿժҪ
	CString m_strSummary;
	HCURSOR m_cur;
	afx_msg void OnLvnItemchangedListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuitemCheck();
	afx_msg void OnNMRclickListResult(NMHDR *pNMHDR, LRESULT *pResult);
};
