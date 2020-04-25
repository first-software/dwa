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
	str += _T("���������ӳɹ���");
	dlg->m_list.AddString(str);
#endif 
	CString Name = _T("����������ӳɹ�!");
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
	CString Name = _T("�����: ");
	Name = dlg->CatShowMsg(Name, strRecv);
	dlg->m_list.AddString(Name);

	//�Զ��ظ� ʱ�� ����: [�Զ��ظ�] �Զ��ظ�����

	if (BST_CHECKED == ((CButton*)dlg->GetDlgItem(IDC_AUTOMSG_CHECK))->GetCheck()) {
		CString strAutoMsg;
		dlg->GetDlgItemText(IDC_AUTOMSG_EDIT, strAutoMsg);
		strAutoMsg = _T("[�Զ��ظ�]: ")+ strAutoMsg;
		dlg->GetDlgItemText(IDC_INITNAME_EDIT, Name);
		Name = dlg->CatShowMsg(Name,strAutoMsg);
		char* SendBuff = T2A(Name);
		Send(SendBuff, SENDMSG_LEN, 0);
		dlg->m_list.AddString(Name);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}
