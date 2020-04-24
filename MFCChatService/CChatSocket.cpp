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

	dlg->m_list.AddString(strRecv);
	CAsyncSocket::OnReceive(nErrorCode);
}