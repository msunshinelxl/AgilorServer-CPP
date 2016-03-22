#if !defined(AFX_BASESOCKETRECEIVETHREAD_H__83174F67_CA5A_43C1_A48B_519DE0EF3C83__INCLUDED_)
#define AFX_BASESOCKETRECEIVETHREAD_H__83174F67_CA5A_43C1_A48B_519DE0EF3C83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseSocketReceiveThread.h : header file
//

class CBaseSocket;

/////////////////////////////////////////////////////////////////////////////
// CBaseSocketReceiveThread thread

class CBaseSocketReceiveThread : public CBaseThread
{
	DECLARE_DYNCREATE(CBaseSocketReceiveThread)
protected:
	CBaseSocketReceiveThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void SetSocket(CBaseSocket* pSocket);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseSocketReceiveThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void TreatSocketEvents(long lTimeOut = 10);
	CBaseSocket* m_pSocket;
	virtual ~CBaseSocketReceiveThread();

	// Generated message map functions
	//{{AFX_MSG(CBaseSocketReceiveThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASESOCKETRECEIVETHREAD_H__83174F67_CA5A_43C1_A48B_519DE0EF3C83__INCLUDED_)
