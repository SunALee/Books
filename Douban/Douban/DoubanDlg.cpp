#include "stdafx.h"
#include "Douban.h"
#include "DoubanDlg.h"
#include ".\doubandlg.h"
#include "common.h"
#include "jsondouban.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDoubanDlg 对话框



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


// CDoubanDlg 消息处理程序

BOOL CDoubanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//初始化下拉列表
	m_ComboType.InsertString(0, "按关键字查询");
	m_ComboType.InsertString(1, "按标签查询");
	m_ComboType.SetCurSel(0);

	//初始化列表框
	m_ListResult.InsertColumn(0, "ID", LVCFMT_CENTER, 80);
	m_ListResult.InsertColumn(1, "书名", LVCFMT_CENTER, 100);
	m_ListResult.InsertColumn(2, "作者", LVCFMT_CENTER, 100);
	m_ListResult.InsertColumn(3, "出版社", LVCFMT_CENTER, 152);
	m_ListResult.InsertColumn(4, "出版时间", LVCFMT_CENTER, 100);
	DWORD dwStyle = m_ListResult.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_ListResult.SetExtendedStyle(dwStyle);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDoubanDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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

	//如果未输入查询内容，则退出
	if (m_strInput.IsEmpty())
	{
		MessageBox("请输入查询内容", _T("错误"), MB_ICONERROR);
		return;
	}
	
	//如果未选择查询方式，则退出
	int index = m_ComboType.GetCurSel();
	if (-1 == index)
	{
		MessageBox("请选择查询方式", _T("错误"), MB_ICONERROR);
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
			
			//遍历列表进行插入
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
	//默认选中第一行
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
		//得到选中项的ID
		int i = m_ListResult.GetNextSelectedItem(position);
		CString strID = m_ListResult.GetItemText(i, 0);
		int nID = atoi(strID);
		
		//遍历书目列表，将对应书目的简介存放到编辑框中
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