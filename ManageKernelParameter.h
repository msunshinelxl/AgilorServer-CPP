#if !defined(AFX_ManageKernelParameter_H__34039D67_81E5_479E_9D3A_A023F68F3D61__INCLUDED_)
#define AFX_ManageKernelParameter_H__34039D67_81E5_479E_9D3A_A023F68F3D61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManageKernelParameter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManageKernelParameter dialog

class CManageKernelParameter : public CDialog
{
// Construction
public:
	CManageKernelParameter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CManageKernelParameter)
	enum { IDD = IDD_MANAGE_KERNEL_PARAMETER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageKernelParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManageKernelParameter)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ManageKernelParameter_H__34039D67_81E5_479E_9D3A_A023F68F3D61__INCLUDED_)
