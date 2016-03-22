// BaseSocketSendThread.h: interface for the CBaseSocketSendThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASESOCKETSENDTHREAD_H__8BBA1E54_5FE7_425F_ADFC_2C6E04C7C1C7__INCLUDED_)
#define AFX_BASESOCKETSENDTHREAD_H__8BBA1E54_5FE7_425F_ADFC_2C6E04C7C1C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBaseSocketSendThread thread

class CBaseSocket;

class CBaseSocketSendThread : public CBaseThread
{
	DECLARE_DYNCREATE(CBaseSocketSendThread)
protected:
	CBaseSocketSendThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void SetSocket(CBaseSocket* pSocket);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseSocketSendThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBaseSocket* m_pSocket;
	virtual ~CBaseSocketSendThread();

	// Generated message map functions
	//{{AFX_MSG(CBaseSocketSendThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif
/////////////////////////////////////////////////////////////////////////////
