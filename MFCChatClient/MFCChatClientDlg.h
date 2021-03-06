﻿
// MFCChatClientDlg.h: 头文件
//

#pragma once
#define RECVMSG_LEN 1024
#define SENDMSG_LEN 1024
#include "CMySocket.h"
// CMFCChatClientDlg 对话框
class CMFCChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATCLIENT_DIALOG };
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
	CString CatShowMsg(CString Name, CString content);
	afx_msg void OnBnClickedConnectBut();
	afx_msg void OnBnClickedDisconnectBut();
	CMySocket* m_socket;
	CListBox m_list;
	CEdit m_Send;
	CTime m_time;
	afx_msg void OnBnClickedSendmsgBut();
	afx_msg void OnBnClickedInitnameBut();
	//afx_msg void OnBnClickedAutomsgRadio();
	afx_msg void OnBnClickedClearscrBut();
	afx_msg void OnBnClickedAutomsgCheck();
	CComboBox m_TextColorCom;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};