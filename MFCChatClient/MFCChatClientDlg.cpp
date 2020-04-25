
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RECVMSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_Send);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_TextColorCom);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BUT, &CMFCChatClientDlg::OnBnClickedConnectBut)
	ON_BN_CLICKED(IDC_DISCONNECT_BUT, &CMFCChatClientDlg::OnBnClickedDisconnectBut)
	ON_BN_CLICKED(IDC_SENDMSG_BUT, &CMFCChatClientDlg::OnBnClickedSendmsgBut)
	ON_BN_CLICKED(IDC_INITNAME_BUT, &CMFCChatClientDlg::OnBnClickedInitnameBut)
	//ON_BN_CLICKED(IDC_AUTOMSG_RADIO, &CMFCChatClientDlg::OnBnClickedAutomsgRadio)
	ON_BN_CLICKED(IDC_CLEARSCR_BUT, &CMFCChatClientDlg::OnBnClickedClearscrBut)
	ON_BN_CLICKED(IDC_AUTOMSG_CHECK, &CMFCChatClientDlg::OnBnClickedAutomsgCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	WCHAR chPath[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, chPath);
	CString strPath;
	strPath.Format(L"%ls//Test.ini", chPath);
	WCHAR chText[MAX_PATH];
	DWORD dWord = GetPrivateProfileString(_T("Client"),_T("Name"),NULL, chText,MAX_PATH,strPath);

	if (dWord <= 0) {
		WritePrivateProfileString(_T("Client"),_T("Name"),_T("客户端"),strPath);
		SetDlgItemText(IDC_INITNAME_EDIT, _T("客户端"));
	}
	else {
		SetDlgItemText(IDC_INITNAME_EDIT, chText);
	}
	//初始化控件状态
	GetDlgItem(IDC_CONNECT_BUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SENDMSG_BUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOMSG_CHECK)->EnableWindow(FALSE);
	//初始化ComboList 控件
	m_TextColorCom.AddString(_T("黑色"));
	m_TextColorCom.AddString(_T("蓝色"));
	m_TextColorCom.AddString(_T("绿色"));
	m_TextColorCom.AddString(_T("红色"));
	m_TextColorCom.SetCurSel(0);
	UpdateData();
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
		CPaintDC dc(this);
		//创建兼容dc
		CDC dcPaint;
		dcPaint.CreateCompatibleDC(&dc);
		//获得工作区窗口大小
		CRect rect;
		GetClientRect(&rect);
		//获得Bitmap位图资源
		CBitmap bitMap;
		bitMap.LoadBitmap(IDB_LOVE_BITMAP);
		//将资源放在BITMAP里面
		BITMAP bBitMap;
		bitMap.GetBitmap(&bBitMap);
		//创建临时数据接收图片资源
		CBitmap* oldB = dcPaint.SelectObject(&bitMap);
		//绘图
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcPaint, 0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectBut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPort, strIp;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIp);

	USES_CONVERSION;
	LPCSTR csPort = (LPCSTR)T2A(strPort);
	LPCSTR csIp = (LPCSTR)T2A(strIp);
	TRACE("csPort = %s,csIp = %s", csPort, csIp);

	int iPort = _ttoi(strPort);
	int iIp = _ttoi(strIp);
	//创建一个Socket对象
	m_socket = new CMySocket;

	//创建一个套接字 容错
	if (!m_socket->Create()) {
		TRACE("create socket err=%d", GetLastError());
		return;
	}
	if (m_socket->Connect(strIp, iPort) == SOCKET_ERROR) {
		TRACE("Connect m_socket err = %d", GetLastError());
		return;
	}
	GetDlgItem(IDC_CONNECT_BUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SENDMSG_BUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOMSG_CHECK)->EnableWindow(TRUE);
	
}


void CMFCChatClientDlg::OnBnClickedDisconnectBut()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_CONNECT_BUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SENDMSG_BUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOMSG_CHECK)->EnableWindow(FALSE);

	CString strDis = _T("与服务器断开连接!");
	strDis = CatShowMsg(strDis, _T(""));
	m_list.AddString(strDis);
	UpdateData(FALSE);
	//回收资源
	m_socket->Close();
	if (m_socket != NULL) {
		delete m_socket;
		m_socket = NULL;
	}
	
}

CString  CMFCChatClientDlg::CatShowMsg(CString Name,CString content) {
	CString strTm;
	CTime m_CatT = CTime::GetCurrentTime();
	strTm = m_CatT.Format("%X ");
	strTm += Name;
	strTm += content;
	return strTm;
}
void CMFCChatClientDlg::OnBnClickedSendmsgBut()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_socket) {
		TRACE("m_socket NOT CREATE err = %d", GetLastError());
		return;
	}
	
	CString strSend;
	m_Send.GetWindowText(strSend);

	

	CString Name;
	GetDlgItemText(IDC_INITNAME_EDIT,Name);
	Name += _T(": ");
	
	strSend = CatShowMsg(Name, strSend);
	
	USES_CONVERSION;
	char* cRecv = T2A(strSend);
	m_socket->Send(cRecv, RECVMSG_LEN, 0);

	m_list.AddString(strSend);
	m_Send.SetSel(0, -1);
	m_Send.Clear();
	UpdateData(FALSE);
}


void CMFCChatClientDlg::OnBnClickedInitnameBut()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK == AfxMessageBox(_T("确定要修改昵称吗？"), MB_OKCANCEL)) {
		CString Name;
		GetDlgItemText(IDC_INITNAME_EDIT, Name);
		if (Name.GetLength() <= 0 || Name.GetLength() > 1024) {
			MessageBox(_T("违规昵称!"));
			return;
		}

		CString strPath;
		//获取当前目录名
		WCHAR chPath[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, chPath);
		strPath.Format(L"%ls//Test.ini", chPath);


		/*LPCSTR lpAppName,//项
			LPCSTR lpKeyName,//键
			LPCSTR lpString,//地址
			LPCSTR lpFileName//姓名
			);*/
			//配置ini表
		WritePrivateProfileString(_T("Client"), _T("Name"), Name, strPath);
	}
	
}


//void CMFCChatClientDlg::OnBnClickedAutomsgRadio()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if (((CButton *)GetDlgItem(IDC_AUTOMSG_RADIO))->GetCheck()) {
//		((CButton*)GetDlgItem(IDC_AUTOMSG_RADIO))->SetCheck(FALSE);
//	}
//	else {
//		((CButton*)GetDlgItem(IDC_AUTOMSG_RADIO))->SetCheck(TRUE);
//	}
//}


void CMFCChatClientDlg::OnBnClickedClearscrBut()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutomsgCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOMSG_CHECK))->GetCheck()) {
		((CButton*)GetDlgItem(IDC_AUTOMSG_CHECK))->SetCheck(FALSE);
	}
	else {
		((CButton*)GetDlgItem(IDC_AUTOMSG_CHECK))->SetCheck(TRUE);
	}
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	
	if (IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID() || IDC_RECVMSG_LIST == pWnd->GetDlgCtrlID()) {
		CString strColor;
		m_TextColorCom.GetWindowText(strColor);
		if (strColor == _T("黑色")) {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == _T("蓝色")) {
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == _T("绿色")) {
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else if (strColor == _T("红色")) {
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		UpdateData(FALSE);
	} 

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) {
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN) {
		if (GetKeyState(VK_CONTROL) < 0) {
			if (pMsg->wParam == 'X') {
				CDialog::OnOK();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
