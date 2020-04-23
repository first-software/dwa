
// MFCChatServiceDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatService.h"
#include "MFCChatServiceDlg.h"
#include "afxdialogex.h"
#include <atlbase.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatServiceDlg 对话框



CMFCChatServiceDlg::CMFCChatServiceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVICE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMFCChatServiceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BUT, &CMFCChatServiceDlg::OnBnClickedStartBut)
	ON_BN_CLICKED(IDC_END_BUT, &CMFCChatServiceDlg::OnBnClickedEndBut)
	ON_BN_CLICKED(IDC_SENDMSG_BUT, &CMFCChatServiceDlg::OnBnClickedSendmsgBut)
END_MESSAGE_MAP()


// CMFCChatServiceDlg 消息处理程序

BOOL CMFCChatServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("6000"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServiceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatServiceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServiceDlg::OnBnClickedStartBut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPort;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	USES_CONVERSION;
	LPCSTR csPort = (LPCSTR)T2A(strPort);
	TRACE("strPort = %s", csPort);
	m_server = new CServerSocket;
	int iPort = _ttoi(strPort);
	if (!m_server->Create(iPort)) {
		TRACE("m_server Create err = %d", GetLastError());
		return;
	}

	if (!m_server->Listen()) {
		TRACE("m_server Listen err = %d", GetLastError());
		return;
	}
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X ");
	str += _T("建立连接!");
	m_list.AddString(str);
	m_list.UpdateData(FALSE);
	
}


void CMFCChatServiceDlg::OnBnClickedEndBut()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatServiceDlg::OnBnClickedSendmsgBut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSend;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strSend);
	USES_CONVERSION;
	char* SendMsg = T2A(strSend);
	m_chat->Send(SendMsg, 200, 0);
	CString str = (_T("我: "));
	m_tm = CTime::GetCurrentTime();
	CString strTm = m_tm.Format("%X ");
	str = strTm + str;
	str += strSend;
	m_list.AddString(str);
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowText(_T(""));
	UpdateData(FALSE);
}
