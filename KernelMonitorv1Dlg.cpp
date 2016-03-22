// KernelMonitorv1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "KernelMonitorv1.h"
//#include "KernelMonitorv1Dlg.h"
#include "ManageKernelParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

DeviceLists::DeviceLists(){
	InitializeCriticalSection(&m_CriticalSection);
}
DeviceLists::~DeviceLists(){
	DeleteCriticalSection(&m_CriticalSection);
}
int DeviceLists::GetSize(){
	return this->deviceNames.size();
}
BOOL DeviceLists::Compare(int index,string str){
	return deviceNames[index].compare(str)==0;
}
void  DeviceLists::Insert(string str){
	EnterCriticalSection(&m_CriticalSection);
	this->deviceNames.insert(this->deviceNames.begin(),str);

	LeaveCriticalSection(&m_CriticalSection);
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKernelMonitorv1Dlg dialog

CKernelMonitorv1Dlg::CKernelMonitorv1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKernelMonitorv1Dlg::IDD, pParent),deviceLists()
{
	//{{AFX_DATA_INIT(CKernelMonitorv1Dlg)
	m_packCount = 0;
	m_packPerSecond = 0;
	m_errorPackCount = 0;
	m_deviceName = _T("Simu11");
	m_uServerPort = 700;
	m_fNetSpeed = 0.0f;
	m_uClientPort = 900;

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_bIsRTDBConnected = FALSE;
	m_bIsDevConnected = FALSE;
	m_sServerIp = _T("127.0.0.1");
	m_sDeviceName = _T("Simu11");
	m_prePackCount = 0;
	m_fNetSpeed = 0.0;
	m_bIsACIConnected = FALSE;
	m_strACIServerName = _T("");
	m_pListenSocket = NULL;
	m_lPackCount = 0;
	m_lDataSize = 0;

	// 客户端连接数
	m_clientCnt = 0;
	m_pListenSocket = NULL; // m_pListenSocket->m_acceptCnt
	pingCount=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CKernelMonitorv1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKernelMonitorv1Dlg)
	DDX_Control(pDX, IDC_RTIP, m_rtdbIP);
	DDX_Text(pDX, IDC_PACKCOUNT, m_packCount);
	DDX_Text(pDX, IDC_PACKPERSECOND, m_packPerSecond);
	//DDX_Text(pDX, IDC_RTDEVICE, m_deviceName);
	DDX_Text(pDX, IDC_RTPORT, m_uServerPort);
	DDX_Text(pDX, IDC_NETSPEED, m_fNetSpeed);
	DDX_Text(pDX, IDC_RTCLIENTPORT, m_uClientPort);

	// 客户端连接数
	DDX_Text(pDX, IDC_CLIENTCNT, m_clientCnt);

	DDX_Text(pDX, IDC_ERRORPACKCOUNT, m_errorPackCount);
	//}}AFX_DATA_MAP
	// 运行消息输出
	DDX_Control(pDX, IDC_LIST_RUNTIME_MSG, m_msgListCtrl);
}


BEGIN_MESSAGE_MAP(CKernelMonitorv1Dlg, CDialog)
	//{{AFX_MSG_MAP(CKernelMonitorv1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONNECTRTDB, OnConnectRTDB)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_MANAGE_POINTS, OnManagePoints)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BTN_STARTSERVICE_VOL, &CKernelMonitorv1Dlg::OnBnClickedBtnStartServiceVol)
	ON_WM_CLOSE()
	//ON_BN_CLICKED(IDC_BTN_STARTSERVICE_OIL, &CKernelMonitorv1Dlg::OnBnClickedBtnStartServiceOil)
	//ON_BN_CLICKED(IDC_BUTTON_STARTSERVICE, &CKernelMonitorv1Dlg::OnBnClickedButtonStartservice)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKernelMonitorv1Dlg message handlers

BOOL CKernelMonitorv1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_rtdbIP.SetAddress(127,0,0,1);

	// 定时
	SetTimer(1, 1000, NULL);	// 1000ms

	// test
	/*CString tmp_str = "2014-11-01 08:00:00";
	long timestamp = DateString2Long(tmp_str);
	CString tmp_str1;
	Agtm_Long2DateString(timestamp, tmp_str1.GetBuffer(32));
	tmp_str1.ReleaseBuffer();*/

	//CString tmp_str0;
	//tmp_str0 = "2014-11-19 10:13:05";
	//long timestamp_01 = DateString2Long(tmp_str0);
	//tmp_str0 = "2014-11-19 10:13:06";
	//long timestamp_02 = DateString2Long(tmp_str0);
	//tmp_str0 = "2014-11-19 10:13:07";
	//long timestamp_03 = DateString2Long(tmp_str0);

	//long timestamp_1 = Agtm_DateTime2Long(10, 13, 5, 2014 - 1900, 11 - 1, 19); // 2014-11-19 10:13:05
	//long timestamp_2 = Agtm_DateTime2Long(10, 13, 6, 2014 - 1900, 11 - 1, 19); // 2014-11-19 10:13:06
	//long timestamp_3 = Agtm_DateTime2Long(10, 13, 7, 2014 - 1900, 11 - 1, 19); // 2014-11-19 10:13:07

	//long timestamp_2 = Agtm_DateTime2Long(8, 0, 0, 2013 - 1900, 12 - 1, 1); // 2013-12-01 08:00:00
	//timestamp_2 += 15808*30*60;
	//CString tmp_str1;
	//Agtm_Long2DateString(timestamp_2, tmp_str1.GetBuffer(32));
	//tmp_str1.ReleaseBuffer();


	/*GetPrivateProfileString("Agilor_Section", "serverIp", "127.0.0.1", m_strServerIp.GetBuffer(32), 32, INI_FILE_PATH);
	m_strServerIp.ReleaseBuffer();
	GetPrivateProfileString("Agilor_Section", "deviceName", "Kernel", m_strDeviceName.GetBuffer(32), 32, INI_FILE_PATH);
	m_strDeviceName.ReleaseBuffer();
	m_uServerPort = GetPrivateProfileInt("Agilor_Section", "serverPort", 700, INI_FILE_PATH);
	m_uClientPort = GetPrivateProfileInt("Agilor_Section", "clientPort", 900, INI_FILE_PATH);
	GetPrivateProfileString("Agilor_Section", "ACIServerName", "Agilor", m_strACIServerName.GetBuffer(32), 32, INI_FILE_PATH);
	m_strACIServerName.ReleaseBuffer();*/


	/*GetPrivateProfileString("Agilor_Section", "hisFileDir", "", m_hisFileDir.GetBuffer(256), 256, INI_FILE_PATH);
	m_hisFileDir.ReleaseBuffer();

	GetPrivateProfileString("MySQL_Section", "host", "127.0.0.1", m_strHost.GetBuffer(32), 32, INI_FILE_PATH);
	m_strHost.ReleaseBuffer();
	GetPrivateProfileString("MySQL_Section", "user", "root", m_strUser.GetBuffer(32), 32, INI_FILE_PATH);
	m_strUser.ReleaseBuffer();
	GetPrivateProfileString("MySQL_Section", "passwd", "", m_strPasswd.GetBuffer(32), 32, INI_FILE_PATH);
	m_strPasswd.ReleaseBuffer();
	GetPrivateProfileString("MySQL_Section", "db", "mychangancar_db", m_strDb.GetBuffer(32), 32, INI_FILE_PATH);
	m_strDb.ReleaseBuffer();
	m_uPort = GetPrivateProfileInt("MySQL_Section", "port", 3306, INI_FILE_PATH);*/
	CString tmpStr;
	GetPrivateProfileString("Agilor_Section", "whiteList", "", tmpStr.GetBuffer(128), 128, INI_FILE_PATH);
	whiteList=strSplit(tmpStr.GetBuffer(0),",");
	m_strHost.ReleaseBuffer();
	//MySQL_library_init();
	Agcn_Startup();

	// 运行状态 + 消息保存
	//m_fileStatusLog = fopen(LOG_FILE_PATH, "at+"); // at+：读写打开一个文本文件，允许读或在文本末追加数据
	//fclose(m_fileStatusLog);
	//m_msgListCtrl.DeleteAllItems();
	m_msgListCtrl.InsertColumn(0, "输出", LVCFMT_LEFT, 550);
	// m_msgListCtrl.InsertColumn(1, "内容", LVCFMT_LEFT, 300);	// LVCFMT_CENTER
	m_msgListCtrl.SetRedraw();	// FALSE

	/*for (int i = 0; i < 12; i++)
	{
		SendAndStoreMessage("shen");
		Sleep(1000);
	}*/

	// ULONGLONG llsize = GetDataSizeOfAgilor();
	LoggerPtr logger(Logger::getLogger(LOG_LOGGER_NAME));
	BasicConfigurator::configure();
	log4cxx::PropertyConfigurator::configure(LOG_PROPERTY);
	LOG4CXX_INFO(logger, "Start Application");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKernelMonitorv1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKernelMonitorv1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKernelMonitorv1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CKernelMonitorv1Dlg::ConnectRTDB()
{
	if (!m_bIsRTDBConnected)
	{
		long hwnd = Agpt_QueryDeviceInfo(m_strACIServerName);
		DEV_INFO dev;
		long id;
		
		while (Agpt_EnumDeviceInfo(hwnd, &id, &dev) != 0){

			// 执行条件判断时程序不响应：1. 未启动数据库；2. 未在数据库中建立设备
			if (DRTDB_RegisterDevice(m_sServerIp.GetBuffer(0), m_uServerPort,dev.szDeviceName)>=0)
			{
				m_bIsRTDBConnected = TRUE;
				//AfxMessageBox(_T("连接RTDB成功！"));
				if (!m_bIsDevConnected)
				{
					m_bIsDevConnected = TRUE;
					DRTDB_SetWindowHandle(m_hWnd);
				}
				string tmpOutput="device connect:";
				tmpOutput.append(dev.szDeviceName);
				deviceLists.Insert(dev.szDeviceName);
				SendAndStoreMessage(tmpOutput.c_str());
			}
			else
			{
				m_bIsRTDBConnected = FALSE;
				AfxMessageBox(_T("连接RTDB失败！"));
				return FALSE;
			}
		}
		m_sServerIp.ReleaseBuffer();
		m_sDeviceName.ReleaseBuffer();
	}
	return TRUE;
}

void CKernelMonitorv1Dlg::DisConnectRTDB()
{
	if (m_bIsRTDBConnected)
	{
		DRTDB_UnregisterDevice("停止数据采集", 0);//设备主动于服务器断连
		m_bIsRTDBConnected = FALSE;
	}

	if (m_bIsDevConnected)
	{
		m_bIsDevConnected = FALSE;
	}
}

void CKernelMonitorv1Dlg::AddPack(long lDataSize, BOOL bErrorPack)
{
	m_baseObj.Lock();
	m_lPackCount++;
	m_lDataSize += lDataSize;
	if (bErrorPack == TRUE) {
		m_errorPackCount++;
	}
	m_baseObj.Unlock();
}

void CKernelMonitorv1Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent) {
		case 1:	// 运行状态监控
			UpdateData(TRUE);
			// 接收统计
			m_packCount = m_lPackCount;						// 数据包计数
			m_packPerSecond = m_packCount - m_prePackCount;	// 数据包速度
			m_fNetSpeed = m_lDataSize / 1000000.0;			// 网速
			m_lDataSize = 0;
			m_prePackCount = m_packCount;
			if(pingCount!=0){
				string tmp="ping count : ";
				char tmpNum[16];
				memset(tmpNum,0,16);
				itoa(pingCount,tmpNum,10);
				tmp.append(tmpNum);
				SendAndStoreMessage(tmp.c_str());
				pingCount;
			}
			// 客户端连接数
			if (m_pListenSocket != NULL)
				m_clientCnt = m_pListenSocket->m_acceptCnt;
			else
				m_clientCnt = 0;

			UpdateData(FALSE);
			break;
		default:	break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CKernelMonitorv1Dlg::OnConnectRTDB() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	// true：更新控件值到对应变量（外部输入交给内部变量）

	unsigned char ip[4];
	m_rtdbIP.GetAddress(ip[0],ip[1],ip[2],ip[3]);
	m_sServerIp.Format(_T("%d.%d.%d.%d"),ip[0],ip[1],ip[2],ip[3]);



	if (!ConnectACI()) { // false
		return;
	}
	if (ConnectRTDB() != FALSE) {
		m_pListenSocket = new CListenSocket();
		m_pListenSocket->m_pDlgPointer = this;
		m_pListenSocket->Create(LOCALPORT, SOCK_STREAM, FD_ACCEPT);	// 10001 TCP
		m_pListenSocket->Listen();
		m_pListenSocket->Start(FALSE);	//线程开启： 0 接收线程  1 发送+接收线程
		//FindTags();
		// DRTDB_SetCallBackFunction(OnNewTagNodeArrive, NULL, NULL, NULL);
	}
	else {
		return;
	}
	CButton* pRadio;
	pRadio = (CButton*)this->GetDlgItem(IDC_CONNECTRTDB);
	pRadio->EnableWindow(!m_bIsACIConnected);
	pRadio = (CButton*)this->GetDlgItem(IDC_MANAGE_POINTS);
	pRadio->EnableWindow(!m_bIsACIConnected);

	pRadio = (CButton*)this->GetDlgItem(IDC_DISCONNECT);
	pRadio->EnableWindow(m_bIsACIConnected);
}
CString CKernelMonitorv1Dlg::getACIServerName(){
	return m_strACIServerName;
}
bool CKernelMonitorv1Dlg::ConnectACI()
{
	if (!m_bIsACIConnected)
	{
		m_strACIServerName = "Agilor";

		//Agcn_GenerateServerName(m_strACIServerName.GetBuffer(0));
		if (m_strACIServerName.IsEmpty())
			m_strACIServerName = _T("Agilor");

		Agcn_CreateNode(m_strACIServerName,m_hWnd,NULL,TRUE);
		long lRes = 0;
		lRes = Agcn_Connect(m_strACIServerName, m_sServerIp, "Guest", "Guest", m_uClientPort);

		if (lRes == 0)
		{
			//MessageBox("ACI连接数据库成功！");
			m_bIsACIConnected = TRUE;
			return true;
		}
		else
		{
			MessageBox("ACI连接数据库失败！！");
			m_bIsACIConnected = FALSE;
			return false;
		}
	}
	return true;
}

BOOL CKernelMonitorv1Dlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_bIsRTDBConnected)
	{
		DisConnectRTDB();
		m_pListenSocket->Stop();
		m_pListenSocket->CloseConnection();
		delete m_pListenSocket;
		m_pListenSocket = NULL;
	}
	if (m_bIsACIConnected)
	{
		Agcn_Disconnect(m_strACIServerName);
		Agcn_RemoveNode(m_strACIServerName);
	}
	Agcn_Cleanup();
	return CDialog::DestroyWindow();
}

void CKernelMonitorv1Dlg::OnDisconnect()
{
	// TODO: Add your control notification handler code here
	DisConnectRTDB();
	m_pListenSocket->Stop(TRUE);	// ?
	m_pListenSocket->CloseConnection();
	delete m_pListenSocket;
	m_pListenSocket = NULL;
	Agcn_Disconnect(m_strACIServerName);
	Agcn_RemoveNode(m_strACIServerName);

	m_bIsACIConnected = FALSE;
	m_bIsRTDBConnected = FALSE;

	// m_tagList.DeleteAllItems();

	CButton* pRadio;
	pRadio = (CButton*)this->GetDlgItem(IDC_CONNECTRTDB);
	pRadio->EnableWindow(!m_bIsACIConnected);
	pRadio = (CButton*)this->GetDlgItem(IDC_DISCONNECT);
	pRadio->EnableWindow(m_bIsACIConnected);
	pRadio = (CButton*)this->GetDlgItem(IDC_MANAGE_POINTS);
	pRadio->EnableWindow(!m_bIsACIConnected);
}

void CKernelMonitorv1Dlg::OnManagePoints() 
{
	// TODO: Add your control notification handler code here
	CManageKernelParameter dlg;
	dlg.DoModal();
}

void CKernelMonitorv1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	// 关闭对话框后解除对mysql_library的依赖
	//MySQL_library_end();

	CDialog::OnClose();
}

// 运行状态消息
void CKernelMonitorv1Dlg::SendAndStoreMessage(CString msg)
{
	char t_s[32];
	time_t lt = time(NULL);
	struct tm _tm;
	localtime_s(&_tm, &lt);
	strftime(t_s, sizeof(t_s), "%Y-%m-%d %H:%M:%S", &_tm);

	if (m_msgListCtrl.GetItemCount() >= 1000)
		m_msgListCtrl.DeleteAllItems();
	int itemCnt = m_msgListCtrl.GetItemCount();
	CString msg_all = t_s;
	msg_all += " " + msg + "\n";
	m_msgListCtrl.InsertItem(itemCnt, msg_all);		//插入行
	m_msgListCtrl.EnsureVisible(itemCnt, FALSE);	// 显示到底部后，可看到最新消息

	LoggerPtr logger(Logger::getLogger(LOG_LOGGER_NAME));
	LOG4CXX_INFO(logger, msg);

	//m_fileStatusLog =_fsopen(LOG_FILE_PATH, "at+", _SH_DENYNO); // at+：读写打开一个文本文件，允许读或在文本末追加数据
	//fwrite(msg_all.GetBuffer(128), msg_all.GetLength(), 1, m_fileStatusLog);
	//msg_all.ReleaseBuffer();
	//fclose(m_fileStatusLog);

	// m_msgListCtrl.SetItemText(0, 1, msg);	//设置该行的不同列的显示字符
	
}