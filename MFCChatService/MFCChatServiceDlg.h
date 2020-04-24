
// MFCChatServiceDlg.h: 头文件
//

#pragma once
#define RECVMSG_LEN 1024
#define SENDMSG_LEN 1024
#include "CServerSocket.h"
#include "CChatSocket.h"
// CMFCChatServiceDlg 对话框
class CMFCChatServiceDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServiceDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVICE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBut();
	afx_msg void OnBnClickedEndBut();
	CListBox m_list;
	CServerSocket* m_server;
	CTime m_tm;
	CChatSocket* m_chat;
	afx_msg void OnBnClickedSendmsgBut();
	CString CatShowMsg(CString Name, CString content);
	afx_msg void OnBnClickedClearscrBut();
};
