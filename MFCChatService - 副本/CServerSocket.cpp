#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServiceDlg.h"

CServerSocket::CServerSocket() {
	
}
CServerSocket::~CServerSocket() {
	
}
void CServerSocket::OnAccept(int nErrorCode) {
	TRACE("######OnAccept");
	CMFCChatServiceDlg* dlg = (CMFCChatServiceDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("与客户端建立连接");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnAccept(nErrorCode);
}