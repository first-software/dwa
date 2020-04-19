#include "pch.h"
#include "CMySocket.h"

CMySocket::CMySocket() {
	
}
CMySocket::~CMySocket() {
	
}
void CMySocket::OnAccept(int nErrorCode) {
	TRACE("####OnAccept");
}
void CMySocket::OnConnect(int nErrorCode) {
	TRACE("####OnConnect");
}