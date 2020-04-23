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
	char RecvBuff[RECVMSG_LEN] = { 0 };
	Receive(RecvBuff, RECVMSG_LEN, 0);
	USES_CONVERSION;
	CString strRecv = (CString)A2T(RecvBuff);
#if 0
	CString str = (_T("客户端: "));
	CString strTm;
	dlg->m_tm = CTime::GetCurrentTime();
	strTm = dlg->m_tm.Format("%X ");
	str = strTm +str;
	str += strRecv;
#endif
	CString str = _T("客户端: ");
	str = dlg->CatShowMsg(str, strRecv);
	dlg->m_list.AddString(str);
	CAsyncSocket::OnReceive(nErrorCode);
}