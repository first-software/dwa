#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServiceDlg.h"

CChatSocket::CChatSocket() {
	
}
CChatSocket:: ~CChatSocket() {
	
}
void CChatSocket::OnReceive(int nErrorCode) {
	TRACE("####OnReceive");
	CMFCChatServiceDlg* dlg = (CMFCChatServiceDlg*)AfxGetApp()->GetMainWnd();
	char RecvBuff[200] = { 0 };
	Receive(RecvBuff, 200, 0);
	USES_CONVERSION;
	CString strRecv = (CString)A2T(RecvBuff);
	CString str = (_T("¿Í»§¶Ë: "));
	CString strTm;
	dlg->m_tm = CTime::GetCurrentTime();
	strTm = dlg->m_tm.Format("%X ");
	str = strTm +str;
	str += strRecv;
	dlg->m_list.AddString(str);
	CAsyncSocket::OnReceive(nErrorCode);
}