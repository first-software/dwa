#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClientDlg.h"
#include "MFCChatClient.h"

CMySocket::CMySocket() {
	
}
CMySocket::~CMySocket() {
	
}

void CMySocket::OnConnect(int nErrorCode) {
	TRACE("####OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
#if 0
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X ");
	str += _T("与服务端连接成功！");
	dlg->m_list.AddString(str);
#endif 
	CString Name = _T("与服务器连接成功!");
	CString Content = _T("");
	Name = dlg->CatShowMsg(Name, Content);
	dlg->m_list.AddString(Name);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####Client  OnReceive");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char RecvBuff[RECVMSG_LEN] = { 0 };
	Receive(RecvBuff, RECVMSG_LEN, 0);
	USES_CONVERSION;
	CString strRecv = (CString)A2T(RecvBuff);
	CString Name = _T("服务端: ");
	Name = dlg->CatShowMsg(Name, strRecv);
	dlg->m_list.AddString(Name);

	//自动回复 时间 姓名: [自动回复] 自动回复内容

	if (BST_CHECKED == ((CButton*)dlg->GetDlgItem(IDC_AUTOMSG_CHECK))->GetCheck()) {
		CString strAutoMsg;
		dlg->GetDlgItemText(IDC_AUTOMSG_EDIT, strAutoMsg);
		strAutoMsg = _T("[自动回复]: ")+ strAutoMsg;
		dlg->GetDlgItemText(IDC_INITNAME_EDIT, Name);
		Name = dlg->CatShowMsg(Name,strAutoMsg);
		char* SendBuff = T2A(Name);
		Send(SendBuff, SENDMSG_LEN, 0);
		dlg->m_list.AddString(Name);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}
