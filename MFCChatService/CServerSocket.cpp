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
	CString Name = _T("与客户端建立连接！");
	CString str = _T("");
	Name = dlg->CatShowMsg(Name, str);
	dlg->m_list.AddString(Name);
	CAsyncSocket::OnAccept(nErrorCode);
}