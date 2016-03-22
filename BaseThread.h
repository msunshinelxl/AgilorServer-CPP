#if !defined(AFX_BASETHREAD_H__6933C5B9_24E3_4067_8E0F_D6B3D105E7B1__INCLUDED_)
#define AFX_BASETHREAD_H__6933C5B9_24E3_4067_8E0F_D6B3D105E7B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseThread.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseThread thread

class CBaseThread : public CWinThread
{
	DECLARE_DYNCREATE(CBaseThread)
protected:
	CBaseThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void Shutdown(BOOL bWaitForShutdown = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Stop();
	BOOL IsStopping(DWORD nTimeOut = 10);
	HANDLE m_hStopEvent;
	HANDLE m_hStopOkEvent;
	HANDLE m_hShutdownEvent;
	virtual ~CBaseThread();

	// Generated message map functions
	//{{AFX_MSG(CBaseThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASETHREAD_H__6933C5B9_24E3_4067_8E0F_D6B3D105E7B1__INCLUDED_)
