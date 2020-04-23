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
#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("��ͻ��˽�������");
#endif
	CString Name = _T("��ͻ��˽������ӣ�");
	CString str = _T("");
	Name = dlg->CatShowMsg(Name, str);
	dlg->m_list.AddString(Name);
	CAsyncSocket::OnAccept(nErrorCode);
}