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
#if 0
	CString str = (_T("服务端: "));
	CString strTm;
	dlg->m_time = CTime::GetCurrentTime();
	strTm = dlg->m_time.Format("%X ");
	str = strTm + str;
	str += strRecv;
	dlg->m_list.AddString(str);
#endif
	CString Name = _T("服务端: ");
	Name = dlg->CatShowMsg(Name, strRecv);
	dlg->m_list.AddString(Name);
	CAsyncSocket::OnReceive(nErrorCode);
}
