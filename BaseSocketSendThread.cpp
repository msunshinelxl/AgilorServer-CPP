// BaseSocketSendThread.cpp : implementation file
//

#include "stdafx.h"
#include "BaseSocketSendThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseSocketSendThread

IMPLEMENT_DYNCREATE(CBaseSocketSendThread, CBaseThread)

CBaseSocketSendThread::CBaseSocketSendThread()
{
	m_pSocket = NULL;
}

CBaseSocketSendThread::~CBaseSocketSendThread()
{
}

BOOL CBaseSocketSendThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	while (m_pSocket == NULL)
		Sleep(1);

	return CBaseThread::InitInstance();
}

int CBaseSocketSendThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CBaseThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CBaseSocketSendThread, CBaseThread)
	//{{AFX_MSG_MAP(CBaseSocketSendThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseSocketSendThread message handlers

int CBaseSocketSendThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bExit = FALSE;
	while (!bExit) {
		if (m_pSocket->SendData(10) == 0) {
			if (IsStopping(0)) {
				bExit = TRUE;
			}
		}
	}

	Stop();
	return ExitInstance();
}

void CBaseSocketSendThread::SetSocket(CBaseSocket *pSocket)
{
	m_pSocket = pSocket;
}
