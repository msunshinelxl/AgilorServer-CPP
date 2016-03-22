// BaseSocket.h: interface for the CBaseSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASESOCKET_H__3B7A6664_5FBC_4A90_A732_2621F54D0A97__INCLUDED_)
#define AFX_BASESOCKET_H__3B7A6664_5FBC_4A90_A732_2621F54D0A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SOCKET_BUFFER_SIZE			10240

class CBaseSocket : public CBaseObject
{
// Attributes
public:
	SOCKET m_hSocket;
	WSAEVENT m_hSocketEvent;
	HANDLE m_hSendAvailable;

public:
	CBaseSocket();
	virtual ~CBaseSocket();
	BOOL Connect( LPCTSTR lpszHostAddress, UINT nHostPort );
	BOOL Create(UINT nSocketPort = 0, int nSocketType = SOCK_STREAM, long lEvent = FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE|FD_ACCEPT, LPCTSTR lpszSocketAddress = NULL);

// Overrides
public:
	long Stop(BOOL bWaitForStopped = TRUE);
	long Start(BOOL bSendSocketData = FALSE);
	long SendData(DWORD nTimeOut);
	long PutData(void* pData, WORD nDataLen, DWORD nTimeOut = 100);
	void Close();
	int Listen(long nConnectBackblog = 5);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);

// Implementation
protected:
	CBaseSocketSendThread* m_pSendThread;
	CBaseSocketReceiveThread* m_pReceiveThread;
	CDataExchangePipe* m_pDataExchangePipe;
	//DoubleQueueBuffer * m_DataExchangePipe;
	char m_pBuffer[SOCKET_BUFFER_SIZE];	// 数据接收缓存
	long m_lPos;

};

#endif // !defined(AFX_BASESOCKET_H__3B7A6664_5FBC_4A90_A732_2621F54D0A97__INCLUDED_)
