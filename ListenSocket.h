// ListenSocket.h: interface for the CListenSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTENSOCKET_H__883C5412_DC5A_41AC_9435_2917007044CB__INCLUDED_)
#define AFX_LISTENSOCKET_H__883C5412_DC5A_41AC_9435_2917007044CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseSocket.h"

class CKernelMonitorv1Dlg;

class CListenSocket : public CBaseSocket  
{
public:
	void CloseConnection();
	void* m_pDlgPointer;
	CListenSocket();
	virtual ~CListenSocket();

// Override
	void OnClose(int nErrorCode);
	void OnAccept(int nErrorCode);

public:
	//CMonitorReceiveSocket* m_pAcceptedSocket;	// 用于控制内核 关闭时不用deal 已包含在m_pAcceptedSocket_0中
	// --- jwj ---
	CMonitorReceiveSocket* m_pAcceptedSocket_0[1024];
	int m_acceptCnt;
	int m_acceptIndex;
	/*SOCKADDR_IN addrClient;
	SOCKADDR*/
	// --- jwj ---
};

#endif // !defined(AFX_LISTENSOCKET_H__883C5412_DC5A_41AC_9435_2917007044CB__INCLUDED_)
