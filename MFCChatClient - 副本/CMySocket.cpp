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
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X ");
	str += _T("与服务端连接成功！");
	dlg->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####Client  OnReceive");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char RecvBuff[200] = { 0 };
	Receive(RecvBuff, 200, 0);
	USES_CONVERSION;
	CString strRecv = (CString)A2T(RecvBuff);
	CString str = (_T("服务端: "));
	CString strTm;
	dlg->m_time = CTime::GetCurrentTime();
	strTm = dlg->m_time.Format("%X ");
	str = strTm + str;
	str += strRecv;
	dlg->m_list.AddString(str);
	
	CAsyncSocket::OnReceive(nErrorCode);
}
