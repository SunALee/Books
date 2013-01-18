#include "stdafx.h"
#include "Douban.h"
#include "DoubanDlg.h"
#include ".\doubandlg.h"
#include "common.h"
#include "jsondouban.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDoubanDlg �Ի���



CDoubanDlg::CDoubanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoubanDlg::IDD, pParent)
	, m_strInput(_T(""))
	, m_nTotal(0)
	, m_nOffset(0)
	, m_nPageNum(0)
	, m_strSummary(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCount = 0;
	m_nOffset = 0;
	m_nTotal = 0;
	m_nType = 0;
}

void CDoubanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ComboType);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ListResult);
	DDX_Text(pDX, IDC_TEXT_TOTAL, m_nTotal);
	DDX_Text(pDX, IDC_TEXT_CUR_PAGE, m_nOffset);
	DDX_Text(pDX, IDC_TEXT_PAGES, m_nPageNum);
	DDV_MinMaxInt(pDX, m_nPageNum, 0, 10000000);
	DDX_Text(pDX, IDC_EDIT_SUMMARY, m_strSummary);
}

BEGIN_MESSAGE_MAP(CDoubanDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SUBMIT, OnBnClickedBtnSubmit)
	ON_STN_CLICKED(IDC_TEXT_PREVIOUS, OnStnClickedTextPrevious)
	ON_STN_CLICKED(IDC_TEXT_NEXT, OnStnClickedTextNext)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RESULT, OnLvnItemchangedListResult)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULT, OnNMClickListResult)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_RESULT, OnLvnItemchangingListResult)
	ON_COMMAND(ID_MENUITEM_CHECK, OnMenuitemCheck)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RESULT, OnNMRclickListResult)
END_MESSAGE_MAP()


// CDoubanDlg ��Ϣ�������

BOOL CDoubanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
// 	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
// 	ASSERT(IDM_ABOUTBOX < 0xF000);
// 
// 	CMenu* pSysMenu = GetSystemMenu(FALSE);
// 	if (pSysMenu != NULL)
// 	{
// 		CString strAboutMenu;
// 		strAboutMenu.LoadString(IDS_ABOUTBOX);
// 		if (!strAboutMenu.IsEmpty())
// 		{
// 			pSysMenu->AppendMenu(MF_SEPARATOR);
// 			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
// 		}
// 	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ�������б�
	m_ComboType.InsertString(0, "���ؼ��ֲ�ѯ");
	m_ComboType.InsertString(1, "����ǩ��ѯ");
	m_ComboType.SetCurSel(0);

	//��ʼ���б��
	m_ListResult.InsertColumn(0, "ID", LVCFMT_CENTER, 80);
	m_ListResult.InsertColumn(1, "����", LVCFMT_CENTER, 100);
	m_ListResult.InsertColumn(2, "����", LVCFMT_CENTER, 100);
	m_ListResult.InsertColumn(3, "������", LVCFMT_CENTER, 152);
	m_ListResult.InsertColumn(4, "����ʱ��", LVCFMT_CENTER, 100);
	DWORD dwStyle = m_ListResult.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_ListResult.SetExtendedStyle(dwStyle);

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CDoubanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDoubanDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CDoubanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDoubanDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here 
	CString strJson;
	GetJSON(strJson, "C");
	if (strJson.IsEmpty())
	{
		return;
	}
	//ApiWriteLog((LPCTSTR)strJson, FALSE);
	CJsonDouBan json;
	JSON_INFO jsonInfo;
	json.Parse(strJson, jsonInfo);
	OnOK();
}
void CDoubanDlg::OnBnClickedBtnSubmit()
{
	UpdateData(TRUE);

	//���δ�����ѯ���ݣ����˳�
	if (m_strInput.IsEmpty())
	{
		MessageBox("�������ѯ����", _T("����"), MB_ICONERROR);
		return;
	}
	
	//���δѡ���ѯ��ʽ�����˳�
	int index = m_ComboType.GetCurSel();
	if (-1 == index)
	{
		MessageBox("��ѡ���ѯ��ʽ", _T("����"), MB_ICONERROR);
		return;
	}

	m_nType = 0;
	switch (index)
	{
	case 0:
		m_nType = SEARCH_KEY;
		break;
	case 1:
		m_nType = SEARCH_TAG;
		break;
	default:
		m_nType = SEARCH_KEY;
		break;
	}

	InitResultList();
}

void CDoubanDlg::InitResultList()
{
	if (GetJSON(m_strJson, m_strInput, m_nType, m_nOffset))
	{
		CJsonDouBan jsonDouban;
		if (jsonDouban.Parse(m_strJson, m_tJson_info))
		{
			m_nOffset = m_tJson_info.m_nOffset+1;
			m_nCount = m_tJson_info.m_nCount;
			m_nTotal = m_tJson_info.m_nTotal;
			if (0 == m_nTotal || 0==m_nCount)
			{
				return;
			}
			m_nPageNum = m_nTotal / m_nCount;
			
			
			m_nPageNum = (0==m_nTotal%m_nCount)?m_nPageNum:++m_nPageNum;

			UpdateData(FALSE);
			
			m_ListResult.DeleteAllItems();
			
			//�����б���в���
			list<BOOK>::iterator itPos;
			int index = 0;
			int nCol = 0;
			for (itPos=m_tJson_info.m_lsBooks.begin(); itPos!=m_tJson_info.m_lsBooks.end(); ++itPos)
			{
				CString strID;
				strID.Format("%d", (*itPos).m_ulID);
				index = m_ListResult.InsertItem(nCol++, strID);
				
				m_ListResult.SetItemText(index, 1, (*itPos).m_strTitle.c_str());
				m_ListResult.SetItemText(index, 2, (*itPos).m_strAuthor.c_str());
				m_ListResult.SetItemText(index, 3, (*itPos).m_strPublisher.c_str());
				m_ListResult.SetItemText(index, 4, (*itPos).m_strPubdate.c_str());
			}
		}
	}
}
void CDoubanDlg::OnStnClickedTextPrevious()
{
	// TODO: Add your control notification handler code here
	if (1 == m_nOffset)
	{
		m_nOffset--;
	}
	if (m_nOffset>=2)
	{
		m_nOffset -= 2;
	}
	InitResultList();
	//Ĭ��ѡ�е�һ��
	m_ListResult.SetItemState(0,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
}

void CDoubanDlg::OnStnClickedTextNext()
{
	// TODO: Add your control notification handler code here
	if (m_nPageNum != 0)
	{
		m_nOffset = m_nOffset%(m_nPageNum+1);
	}
	InitResultList();

	m_ListResult.SetItemState(0,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED); 
}

void CDoubanDlg::OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION position = m_ListResult.GetFirstSelectedItemPosition();
	if (position != NULL)
	{
		//�õ�ѡ�����ID
		int i = m_ListResult.GetNextSelectedItem(position);
		CString strID = m_ListResult.GetItemText(i, 0);
		int nID = atoi(strID);
		
		//������Ŀ�б�����Ӧ��Ŀ�ļ���ŵ��༭����
		list<BOOK>::iterator itPos;
		for (itPos=m_tJson_info.m_lsBooks.begin(); itPos!=m_tJson_info.m_lsBooks.end(); ++itPos)
		{
			if ((*itPos).m_ulID == nID)
			{
				m_strSummary = (*itPos).m_strSummary.c_str();
				UpdateData(FALSE);
				break;
			}
		}
	}
	*pResult = 0;
}

void CDoubanDlg::OnLvnItemchangedListResult( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	OnNMClickListResult(pNMHDR, pResult);
	*pResult = 0;
}

void CDoubanDlg::OnLvnItemchangingListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	OnNMClickListResult(pNMHDR, pResult);
	*pResult = 0;
}

void CDoubanDlg::OnMenuitemCheck()
{
	POSITION position = m_ListResult.GetFirstSelectedItemPosition();
	if (position != NULL)
	{
		int i = m_ListResult.GetNextSelectedItem(position);
		CString strID = m_ListResult.GetItemText(i, 0);
		if (strID.IsEmpty())
		{
			return;
		}
		CString strUrl = _T("http://book.douban.com/subject/") + strID;
		ShellExecute(NULL, _T("open"), strUrl, NULL, NULL, SW_SHOW);
	}
}

void CDoubanDlg::OnNMRclickListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_CHECK));
		CMenu *pMenu = menu.GetSubMenu(0);
		if (NULL != pMenu)
		{
			pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
		}
	}
	*pResult = 0;
}