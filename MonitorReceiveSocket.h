// MonitorReceiveSocket.h: interface for the CMonitorReceiveSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORRECEIVESOCKET_H__39910150_1AA7_47F4_9A99_4679C0BFB1AF__INCLUDED_)
#define AFX_MONITORRECEIVESOCKET_H__39910150_1AA7_47F4_9A99_4679C0BFB1AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseSocket.h"
#include "ACI_H.H"
#include "DoubleQueueBuffer.h"
//#include "DataExecutor.h"
class CListenSocket;
class DataExecutor;
class CMonitorReceiveSocket : public CBaseSocket
{
	//friend DataExecutor;
	
	
public:
	void* m_pDlgPointer;
	//void ParsePackage();
	CMonitorReceiveSocket();
	//void CMonitorReceiveSocket::MyPutData(byte* data,int length);
	virtual ~CMonitorReceiveSocket();
	CListenSocket* m_pListenSocket;	// class前添加class CListenSocket;声明，CListenSocket与CMonitorReceiveSocket相互使用时编译出错
	DoubleQueueBuffer * recvBuffer;
	DataExecutor* m_pParser;
// Override
	void OnConnect(int nErrorCode);
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
	union UStuff
	{
		float   f;
		unsigned char   c[0];
		int i;
	};

	long Stop(BOOL bWaitForStopped = TRUE);
	long Start(BOOL bSendSocketData = FALSE);
	int recvFailCount;
//private:
//	void parseBaseToken(BaseType* res,int *st,int length,char* data);
};

#endif // !defined(AFX_MONITORRECEIVESOCKET_H__39910150_1AA7_47F4_9A99_4679C0BFB1AF__INCLUDED_)
