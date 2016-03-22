// BaseSocket.cpp: implementation of the CBaseSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseSocket::CBaseSocket()
{
	m_hSocketEvent = WSACreateEvent();
	m_hSocket = INVALID_SOCKET;
	m_lPos = 0;
	m_pDataExchangePipe = new CDataExchangePipe(10);
	m_hSendAvailable = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_pReceiveThread = NULL;
	m_pSendThread = NULL;
}

CBaseSocket::~CBaseSocket()
{
	Stop();
	Close();
	delete m_pDataExchangePipe;
	m_pDataExchangePipe = NULL;
	CloseHandle(m_hSendAvailable);
}

BOOL CBaseSocket::Create(UINT nSocketPort, int nSocketType, long lEvent, LPCTSTR lpszSocketAddress)
{
	// 创建TCP套接字
	m_hSocket = socket(AF_INET, nSocketType, 0);
	if (INVALID_SOCKET == m_hSocket) {
		MessageBox(NULL, _T("套接字创建失败！"), _T("错误"), MB_ICONERROR);
		m_hSocket = NULL;
		return FALSE;
	}

	if (SOCKET_ERROR == WSAEventSelect(m_hSocket, m_hSocketEvent, lEvent)) {
		MessageBox(NULL, _T("事件与网络关联失败！"), _T("错误"), MB_ICONERROR);
		::closesocket(m_hSocket);
		m_hSocket = NULL;
		return FALSE;
	}

	// ip与端口设置
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));
	LPSTR lpszAscii = (LPSTR)lpszSocketAddress;
	sockAddr.sin_family = AF_INET;
	if (NULL == lpszAscii) {	// 本地IP地址为空时可向任何分配给本机机器的IP地址发或收数据
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else {
		DWORD lResult = inet_addr(lpszAscii);
		if (INADDR_NONE == lResult) {
			MessageBox(NULL, _T("IP地址有误！"), _T("错误"), MB_ICONERROR);
			// WSASetLastError(WSAEINVAL);
			return FALSE;
		}
		sockAddr.sin_addr.s_addr = lResult;
	}
	sockAddr.sin_port = htons((u_short)nSocketPort);

	if (SOCKET_ERROR == bind(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr))) {
		MessageBox(NULL, _T("套接字绑定失败！"), _T("错误"), MB_ICONERROR);
		return FALSE;
	}
		
	return TRUE;
}

BOOL CBaseSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	SOCKADDR_IN sa;

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(lpszHostAddress);
	sa.sin_port = htons(nHostPort);

	if(m_hSocket!=INVALID_SOCKET)
	{
		if(SOCKET_ERROR == connect(m_hSocket,(SOCKADDR*)&sa,sizeof(sa)))
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return FALSE;
			}
			else
				return TRUE;
		}
		else
			return TRUE;
	}
	else
		return FALSE;
}

void CBaseSocket::OnClose(int nErrorCode) 
{
	
}

void CBaseSocket::OnSend(int nErrorCode) 
{
	SetEvent(m_hSendAvailable);
}

void CBaseSocket::OnConnect(int nErrorCode) 
{
	
}

void CBaseSocket::OnReceive(int nErrorCode) 
{
	
}

void CBaseSocket::OnAccept(int nErrorCode) 
{

}

int CBaseSocket::Listen(long nConnectBackblog)
{
	return listen(m_hSocket, nConnectBackblog);
}

void CBaseSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		WSACloseEvent(m_hSocketEvent);
		shutdown(m_hSocket, 0);
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
}

long CBaseSocket::PutData(void *pData, WORD nDataLen, DWORD nTimeOut)
{
	Lock();
	if (m_pDataExchangePipe->PutDataEx(pData, nDataLen, nTimeOut))
	{
		Unlock();
		return RS_OK;
	}
	else
	{
		Unlock();
		return RS_SOCKET_BUFFER_FULL;
	}
}

long CBaseSocket::SendData(DWORD nTimeOut)
{
	DataExchangeBlock* pData;
	if (pData = m_pDataExchangePipe->GetDataExchangeBlock())
	{
		long lSentSize = 0;
		long lRes;
		BOOL bError = FALSE;
		
		while ((lSentSize < pData->wDataLen) && !bError)
		{
			ResetEvent(m_hSendAvailable);
			lRes = send(m_hSocket, (const char*)(pData->lpData + lSentSize), pData->wDataLen - lSentSize, 0);
			if (lRes == SOCKET_ERROR)
			{
				switch (GetLastError())
				{
				case WSAEWOULDBLOCK:
					WaitForSingleObject(m_hSendAvailable, nTimeOut);
					break;
				default:
					bError = TRUE;
					break;
				}
			}
			else
			{
				lSentSize += lRes;
			}
		}
		return lRes;
	}
	else
		return 0;
}

long CBaseSocket::Start(BOOL bSendSocketData)
{
	if (INVALID_SOCKET == m_hSocket) {
		return RS_INVALID_SOCKET;
	}

	m_pReceiveThread = (CBaseSocketReceiveThread*)::AfxBeginThread(RUNTIME_CLASS(CBaseSocketReceiveThread));
	m_pReceiveThread->SetSocket(this);

	if (FALSE != bSendSocketData) {
		m_pSendThread = (CBaseSocketSendThread*)::AfxBeginThread(RUNTIME_CLASS(CBaseSocketSendThread));
		m_pSendThread->SetSocket(this);
	}

	return RS_OK;
}

long CBaseSocket::Stop(BOOL bWaitForStopped)
{
	if (m_hSocket == INVALID_SOCKET)
	{
		return RS_INVALID_SOCKET;
	}
	if (m_pReceiveThread)
	{
		m_pReceiveThread->Shutdown(bWaitForStopped);
		//m_pReceiveThread->Delete();
		m_pReceiveThread = NULL;
	}
	if (m_pSendThread)
	{
		m_pSendThread->Shutdown(TRUE);
		//m_pSendThread->Delete();
		m_pSendThread = NULL;
	}
	return RS_OK;
}
