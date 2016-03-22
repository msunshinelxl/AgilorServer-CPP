// ManageKernelParameter.cpp : implementation file
//

#include "stdafx.h"
#include "KernelMonitorv1.h"
#include "ManageKernelParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManageKernelParameter dialog


CManageKernelParameter::CManageKernelParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CManageKernelParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageKernelParameter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CManageKernelParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManageKernelParameter)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManageKernelParameter, CDialog)
	//{{AFX_MSG_MAP(CManageKernelParameter)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageKernelParameter message handlers
