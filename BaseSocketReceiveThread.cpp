// BaseSocketReceiveThread.cpp : implementation file
//

#include "stdafx.h"
#include "BaseSocketReceiveThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseSocketReceiveThread

IMPLEMENT_DYNCREATE(CBaseSocketReceiveThread, CBaseThread)

CBaseSocketReceiveThread::CBaseSocketReceiveThread()
{
	m_pSocket = NULL;
}

CBaseSocketReceiveThread::~CBaseSocketReceiveThread()
{
}

BOOL CBaseSocketReceiveThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	while (m_pSocket == NULL)
		Sleep(1);

	return CBaseThread::InitInstance();
}

int CBaseSocketReceiveThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CBaseThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CBaseSocketReceiveThread, CBaseThread)
	//{{AFX_MSG_MAP(CBaseSocketReceiveThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseSocketReceiveThread message handlers

int CBaseSocketReceiveThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bExit = FALSE;
	while (!bExit)
	{
		TreatSocketEvents();
		if (IsStopping(0))
		{
			bExit = TRUE;
		}
	}

	Stop();
	
	return ExitInstance();
}

void CBaseSocketReceiveThread::SetSocket(CBaseSocket *pSocket)
{
	m_pSocket = pSocket;
}

void CBaseSocketReceiveThread::TreatSocketEvents(long lTimeOut)
{
	WSANETWORKEVENTS netEvents;
	DWORD nRes;
	nRes = WSAWaitForMultipleEvents(1, &(m_pSocket->m_hSocketEvent), FALSE, lTimeOut, FALSE);	// 一个事件有信号就触发
	if (nRes == WSA_WAIT_EVENT_0)
	{
		if (WSAEnumNetworkEvents(m_pSocket->m_hSocket, m_pSocket->m_hSocketEvent, &netEvents) != SOCKET_ERROR)
		{
			if (FD_ACCEPT == (netEvents.lNetworkEvents & FD_ACCEPT)) {	// 请求到来时，接收请求
				m_pSocket->OnAccept(netEvents.iErrorCode[FD_ACCEPT_BIT]);
			}

			if (FD_READ == (netEvents.lNetworkEvents & FD_READ)) {	// 接收数据
				m_pSocket->OnReceive(netEvents.iErrorCode[FD_READ_BIT]);
			}

			if (FD_WRITE == (netEvents.lNetworkEvents & FD_WRITE)) {
				m_pSocket->OnSend(netEvents.iErrorCode[FD_WRITE_BIT]);
			}

			if (FD_CLOSE == (netEvents.lNetworkEvents & FD_CLOSE)) {	// 客户端丢失连接时关闭前连接
				m_pSocket->OnClose(netEvents.iErrorCode[FD_CLOSE_BIT]);
			}

			// --- jwj ---
			if (FD_CONNECT == (netEvents.lNetworkEvents & FD_CONNECT)) {
				m_pSocket->OnConnect(netEvents.iErrorCode[FD_CONNECT_BIT]);
			}
			// --- jwj ---
		}
	}
}
