// BaseThread.cpp : implementation file
//

#include "stdafx.h"
#include "BaseThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseThread

IMPLEMENT_DYNCREATE(CBaseThread, CWinThread)

CBaseThread::CBaseThread()
{
}

CBaseThread::~CBaseThread()
{
}

BOOL CBaseThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	// 人工重置事件
	m_hStopOkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	return TRUE;
}

int CBaseThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	CloseHandle(m_hStopEvent);
	CloseHandle(m_hStopOkEvent);
	CloseHandle(m_hShutdownEvent);

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CBaseThread, CWinThread)
	//{{AFX_MSG_MAP(CBaseThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseThread message handlers

void CBaseThread::Shutdown(BOOL bWaitForShutdown)
{
	SetEvent(m_hStopEvent);
	if (bWaitForShutdown)
	{
		WaitForSingleObject(m_hStopOkEvent, INFINITE);
		SetEvent(m_hShutdownEvent);
	}
}

BOOL CBaseThread::IsStopping(DWORD nTimeOut)
{
	return (WaitForSingleObject(m_hStopEvent, nTimeOut) == WAIT_OBJECT_0);
}

void CBaseThread::Stop()
{
	SetEvent(m_hStopOkEvent);
	WaitForSingleObject(m_hShutdownEvent, INFINITE);
}
