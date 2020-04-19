#pragma once
#include <afxsock.h>
class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};

