// KernelMonitorv1Dlg.h : header file
//

#if !defined(AFX_KERNELMONITORV1DLG_H__AC5585F8_BC35_4402_9DDB_2576D51E0B35__INCLUDED_)
#define AFX_KERNELMONITORV1DLG_H__AC5585F8_BC35_4402_9DDB_2576D51E0B35__INCLUDED_

#include "stdafx.h"
#include "ListenSocket.h"	// Added by ClassView
#include "afxcmn.h"
#include <vector>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKernelMonitorv1Dlg dialog
#define LOCALPORT 10001
#define ONEYEAR_TIMESTAMP	365*24*60*60	//  20*60
using namespace std;


typedef struct struct_statistics {
	char car_type_id[17];
	int level;
	int lval;
	int car_count;
	int range[26];
}VOL_INFO, OIL_INFO;

class DeviceLists{
	vector<string> deviceNames;
	CRITICAL_SECTION m_CriticalSection;
public :
	int GetSize();
	BOOL Compare(int,string);
	void Insert(string str);
	DeviceLists();
	virtual ~DeviceLists();
};



class CKernelMonitorv1Dlg : public CDialog
{
// Construction
public:
	void AddPack(long lDataSize, BOOL bErrorPack);
	CBaseObject m_baseObj;

	void DisConnectRTDB();
	BOOL m_bIsRTDBConnected;
	BOOL m_bIsDevConnected;
	CListenSocket* m_pListenSocket;
	CString m_sServerIp;
	CString m_sDeviceName;
	CString m_sFullTagName;
	vector<string> whiteList;
	BOOL ConnectRTDB();
	CKernelMonitorv1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKernelMonitorv1Dlg)
	enum { IDD = IDD_KERNELMONITORV1_DIALOG };
	CIPAddressCtrl	m_rtdbIP;
	UINT	m_packCount;
	UINT	m_packPerSecond;
	UINT	m_errorPackCount;
	CString	m_deviceName;
	UINT	m_uServerPort;
	double	m_fNetSpeed;
	UINT	m_uClientPort;
	int pingCount;
	int pingCountOld;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKernelMonitorv1Dlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_lPackCount;
	UINT m_prePackCount;
	long m_lDataSize;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKernelMonitorv1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConnectRTDB();
	afx_msg void OnDisconnect();
	afx_msg void OnManagePoints();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strACIServerName;
	BOOL m_bIsACIConnected;
	bool ConnectACI();
	
	// void FindTags();
public:
	BOOL m_bIsStartService_Voltage;
	BOOL m_bIsStartService_Oilwear;
	DeviceLists deviceLists;
	// CString m_strServerIp, m_strDeviceName, m_strACIServerName;
	// unsigned int m_uServerPort, m_uClientPort;
	CString m_hisFileDir;
	CString m_strHost, m_strUser, m_strPasswd, m_strDb;
	unsigned int m_uPort;

	unsigned int m_clientCnt;	// 客户端连接数

	afx_msg void OnClose();

	// 运行状态
	CListCtrl m_msgListCtrl;
	void SendAndStoreMessage(CString msg);
	FILE *m_fileStatusLog;
	
public:
	CString getACIServerName();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KERNELMONITORV1DLG_H__AC5585F8_BC35_4402_9DDB_2576D51E0B35__INCLUDED_)
