//*****************************************
//***      Agilor Call Interface        ***
//***   Right reserved by IEL@ISCAS     ***
//***       2004.2 created by wq        ***
//*****************************************

#ifndef _AGILOR_CALL_INTERFACE_H_
#define _AGILOR_CALL_INTERFACE_H_

//****************************
#define MAX_SERVER_NUMBER		4	//the max number of server supported
#define EVENT_WAIT_TIMEOUT		30000
#define AGILOR_SERVICE_PORT		900
#define SUB_DATA_BUFFER_SIZE	30000

//******�������ڵ�����״̬******
#define AG_NODE_STATE_INVALID		0
#define AG_NODE_STATE_CONNECTED		1
#define AG_NODE_STATE_DISCONNECTED	2

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

//*********������Ϣ�����¼�*********
#define	WM_SUBDATAARRIVAL		WM_USER+101	//monitor the arrival of sub data
#define	WM_DISCONNECTED			WM_USER+102	//monitor the connection with server
#define EVENT_SUBDATAARRIVAL	"AGNE_SUBDATAARRIVAL"
#define EVENT_DISCONNECTED		"AGNE_DISCONNECTED"	


//wk, 2005.10.20, add:
#ifdef __cplusplus

//****** �ؼ��ֶγ��ȶ��� ******
const DWORD C_FULL_TAGNAME_LEN	=	80;	//SERVERNAME.TAGNAME, sucha as LGCAG.ZL_AI1001
const DWORD C_SERVERNAME_LEN	=	16;	
const DWORD C_SERVERADDR_LEN	=	16;
const DWORD C_USERNAME_LEN		=	32;
const DWORD C_PASSWORD_LEN		=	16;
const DWORD C_TAGNAME_LEN		=	64;	//maybe some tags on different server have the same name
const DWORD C_TAGDESC_LEN		=	32;
const DWORD C_TAGUNIT_LEN		=	16;
const DWORD C_DEVICENAME_LEN	=	32;
const DWORD C_GROUPNAME_LEN		=	32;
const DWORD C_STRINGVALUE_LEN	=	128;
const DWORD C_SOURCETAG_LEN		=	128;	//the physical tag on devices
const DWORD C_ENUMDESC_LEN		=	128;	

//****** ���ݵ㱨��״̬λ *********
// -- jwj -- const WORD ALARM_TYPE_HILIMIT_MASK		= 0x0001;	//�߱��� 
// -- jwj -- const WORD ALARM_TYPE_LOLIMIT_MASK		= 0x0002;	//�ͱ��� 
// -- jwj -- const WORD ALARM_TYPE_HIHILIMIT_MASK	= 0x0004;	//�߸߱���
// -- jwj -- const WORD ALARM_TYPE_LOLOLIMIT_MASK	= 0x0008;	//�͵ͱ���
// -- jwj -- const WORD ALARM_TYPE_SWITCHON_MASK		= 0x0010;	//������ 
// -- jwj -- const WORD ALARM_TYPE_SWITCHOFF_MASK	= 0x0020;	//�ر��� 

//****** �������ݲɼ���־ *********
// -- jwj -- const BYTE SCAN_INPUT		= 0x01;	//��������
// -- jwj -- const BYTE SCAN_OUTPUT		= 0x02;	//�������
const BYTE SCAN_DISABLE		= 0x80;	//��ֹI/O

//wk, 2005.10.20, add:
#endif

//wk, 2005.10.20, add ->

#ifndef __cplusplus

//****** �ؼ��ֶγ��ȶ��� ******
#define C_FULL_TAGNAME_LEN	80	//SERVERNAME.TAGNAME, sucha as LGCAG.ZL_AI1001
#define C_SERVERNAME_LEN	16	
#define C_SERVERADDR_LEN	16
#define C_USERNAME_LEN		32
#define C_PASSWORD_LEN		16
#define C_TAGNAME_LEN		64	//maybe some tags on different server have the same name
#define C_TAGDESC_LEN		32
#define C_TAGUNIT_LEN		16
#define C_DEVICENAME_LEN	32
#define C_GROUPNAME_LEN		32
#define C_STRINGVALUE_LEN	128
#define C_SOURCETAG_LEN		128	//the physical tag on devices
#define C_ENUMDESC_LEN		128	

//****** ���ݵ㱨��״̬λ *********
#define ALARM_TYPE_HILIMIT_MASK		0x0001	//�߱��� 
#define ALARM_TYPE_LOLIMIT_MASK		0x0002	//�ͱ��� 
#define ALARM_TYPE_HIHILIMIT_MASK	0x0004	//�߸߱���
#define ALARM_TYPE_LOLOLIMIT_MASK	0x0008	//�͵ͱ���
#define ALARM_TYPE_SWITCHON_MASK	0x0010	//������ 
#define ALARM_TYPE_SWITCHOFF_MASK	0x0020	//�ر��� 

//****** �������ݲɼ���־ *********
#define SCAN_INPUT		0x01	//��������
#define SCAN_OUTPUT		0x02	//�������
#define SCAN_DISABLE	0x80	//��ֹI/O

#endif

#define DEVICE_STATE_TAG_NAME_PREFIX	"%#_DeviceState_"

//<- wk, 2005.10.20, add


//****** ��ʷ����ͳ�ƺ��� *********
/* wk, 2005.11.17, del:
#define SUMMARY_ARCTOTAL	1		//ͳ�����
#define SUMMARY_ARCMINIMUM	2		//���ֵ
#define SUMMARY_ARCMAXIMUM	3		//��Сֵ
#define SUMMARY_ARCRANGE	4		//�仯��Χ
#define SUMMARY_ARCAVERAGE	5		//����ƽ��ֵ
*/


typedef struct struServer_Info
{
	_TCHAR	szServerName[C_SERVERNAME_LEN];
	_TCHAR szServerAddr[C_SERVERADDR_LEN];
	_TCHAR szUserName[C_USERNAME_LEN];
	_TCHAR szPassword[C_PASSWORD_LEN];
	BOOL bIsConnected;
}SERVER_INFO;

typedef struct struDevice_Info{
	_TCHAR szDeviceName[C_DEVICENAME_LEN];
	BOOL bIsOnline;
}DEV_INFO;

typedef struct struTagNode
{
	char	name[C_TAGNAME_LEN];		//@*�ɼ����ݵ���(����)
	char	descriptor[32];		//*����
	char	engunits[16];		//*�ɼ������ݵ�λ
	long	pointid;		//@�ɼ����ݵ���
	BYTE	pointtype;		//*@�ɼ�����������//(R������/S�ַ���/B����/L����/Eö��)
	BYTE	scan;			//*@�������ݲɼ���־(IO status)	  0��>=0x80("��ֹ"),1("����"),2("���")
	WORD    reserved1;
	float	typicalvalue;		//����ֵ//WQ@2003-9-10
	//	float	displaydigits;		//�ɼ���������ʾȱʡ����
    
	union {							//@��ǰֵ(��ʼֵ)
		float	rval;		// ����	
		long	lval;		// ����
		BOOL	bval;		// ����
		char	sval[C_STRINGVALUE_LEN];// �ַ���
		//wk, 2005.10.20, del: struct EVAL{
		//wk, 2005.10.20, add:
		struct {
			short	type;					// 0x0001��ʾʹ��key,0x0002��ʾʹ��name (0x0003 ��ʾͬʱʹ��key,name),
			short	key;					// ö��(ֵ)	
			char	name[C_STRINGVALUE_LEN];	// ö��(�ַ���)
		}eval;						 // ö��
	};
	char	enumdesc[C_ENUMDESC_LEN];	//*@ö������   eg. "2:1,2,on:0,3,off" 
			// "ö�ٸ���:��־1,ö����1����,ö����1:��־2,ö����2����,ö����2...   

	long	timedate;		//@ʱ���
	long	istat;			//@��״̬

	char	sourceserver[C_DEVICENAME_LEN];	//*�ɼ��������Դվ(�豸��)
	char	sourcegroup[32];	//*�ɼ��������Դ�����
	//WQ@2003-9-10/char	sourcetag[32];		//*@�ɼ��������Դ���(��λ��)
	char	sourcetag[C_SOURCETAG_LEN];
	//	float   zero;			//���ݷ�����ֵ
	float   upperlimit;			//��������
	float	lowerlimit;			//��������

	WORD	pushref1;		//@ʵʱ���������־
	WORD	ruleref1;		//@ʵʱ���������־
	
	//BYTE	tagonline;		//@�������ݴ�����״̬
	//BYTE	newtag;			//@ֵ���±�־
	long	excmin;			//*ʵʱ���ݴ�����̼�����������ڣ�
	long	excmax;			//*ʵʱ���ݴ��������
	float   excdev;			//*ʵʱ���ݴ���������

	//long	ptalarm;		//�������ݱ���¼��
	WORD	alarmtype;		//*����
	WORD	alarmstate;		//״̬����
	float	alarmmax;		//*���ޱ���
	float	alarmmin;		//*���ޱ���
	float	alarmhihi;
	float	alarmlolo;

	//wk, 2003.9, add ->
	WORD	hipriority;			//�������ȼ�����ʱ������
	WORD	lopriority;
	WORD	hihipriority;
	WORD	lolopriority;
	//<- wk, 2003.9, add

	BYTE	archiving;		//*�Ƿ�洢��ʷ����
	BYTE	compressing;		//*�Ƿ������ʷѹ��
	BYTE	step;			//*��ʷ���ݵĲ�ֵ��ʽ�����Σ�̨�ף�
	BYTE	reserved2;
	long	hisidx;			//��ʷ��¼������
	long	compmin;		//*ѹ����ϼ��
	long	compmax;		//*ѹ������
	float	compdev;		//*ѹ��������

	float	lastval;		//�ϴ����ݴ浵��ֵ
	long	lasttime;		//�ϴ����ݴ浵��ʱ��

	long	creationdate;		//�ɼ��㴴������
	//	char	creator[16];		//�ɼ��㴴����
	//	long	changedate;		//�ɼ�������޸�����
	//	char	changer[16];		//�ɼ�������޸���

	//	short	ptowner;		//���ӵ����
	//	short	ptgroup;		//���������
	//	BYTE	ptAccess;		//�����Ȩ��	
} TAG_NODE;

//****** ���Ͷ���-���ݵ㶨�� ******
typedef struct struTagNode_Define{
	_TCHAR	TagName[C_TAGNAME_LEN];			//�ɼ����ݵ���-(Required)
	_TCHAR	TagDesc[C_TAGDESC_LEN];			//����-(Optional)
	_TCHAR	EngUnit[C_TAGUNIT_LEN];			//�ɼ������ݵ�λ-(Optional)
	BYTE	TagType;						//��������(R����/S�ַ���/B����/L����)-(Rrequired)
	float	TypicalVal;						//����ֵ-(Optional, default =0)
	_TCHAR	DeviceName[C_DEVICENAME_LEN];	//�ɼ��������Դվ-(Required) 
	_TCHAR	GroupName[C_GROUPNAME_LEN];		//�ɼ��������Դ�����-(Optional)
	_TCHAR	SourceTag[C_SOURCETAG_LEN];		//�ɼ��������Դ���-(Optional)
	BYTE	IOState;						//�������ݲɼ���,0-"��ֹ",1-"����",2-"���"-(Rrequired)
	long	ExceptionMin;					//���ݴ�����̼��-��������, default = 1
	long	ExceptionMax;					//���ݴ��������, default = 1
	float 	ExceptionDev;					//���ݴ���������, default = 0
	float 	UpperLimit;						//��������-(Optional, default = 0)
	float	LowerLimit;						//��������-(Optional, default = 0)
	WORD 	AlarmType;						//��������, default = 0
	float	AlarmHiHi;						//�߸߱���, default = 0
	float	AlarmHi;						//�߱���, default = 0
	float	AlarmLo;						//�ͱ���, default = 0
	float	AlarmLoLo;						//�͵ͱ���, default = 0
	BYTE	IsArchived;						//�Ƿ�洢��ʷ����, default = 0
	BYTE	IsCompressed;					//�Ƿ������ʷѹ��, default = 1
	BYTE	InterMethod;					//��ʷ���ݵĲ�ֵ��ʽ(����/̨��)
	long	CompressMin;					//ѹ����ϼ��
	long	CompressMax;					//ѹ������
	float	CompressDev;					//ѹ��������
	long	CreationDate;					//�ɼ��㴴������
}TAG_DEF; 

//****** ���Ͷ���-���ݵ���Ϣ ******
typedef struct struTagNode_Info{
	_TCHAR	TagName[C_TAGNAME_LEN];			//�ɼ����ݵ���-(Required)
	_TCHAR	TagDesc[C_TAGDESC_LEN];			//����-(Optional)
	_TCHAR	EngUnit[C_TAGUNIT_LEN];			//�ɼ������ݵ�λ-(Optional)
	long	TagID;							//Unique ID, Integer
	BYTE	TagType;						//��������(R����/S�ַ���/B����/L����)-(Rrequired)
	BYTE	IOState;						//�������ݲɼ���,0-"��ֹ",1-"����",2-"���"-(Rrequired)
	WORD	Reserved1;
	float	TypicalVal;						//����ֵ-(Optional, default =0)
	union {									//��ǰֵ
		float	rval;					// ����	
		long	lval;					// ����
		BOOL	bval;					// ����
		_TCHAR	sval[C_STRINGVALUE_LEN];// �ַ���
		//wk, 2005.10.20, del: struct EVAL{
		//wk, 2005.10.20, add:
		struct {
			short	type;					// 0x0001��ʾʹ��key,0x0002��ʾʹ��name
			short	key;					// ö��(ֵ)	
			_TCHAR	name[C_STRINGVALUE_LEN];	// ö��(�ַ���)
		}eval;							// ö��
	};
	_TCHAR	EnumDesc[C_ENUMDESC_LEN];		//ö������
	long	Timestamp;						//ʱ���
	long	TagState;						//��״̬
	_TCHAR	DeviceName[C_DEVICENAME_LEN];	//�ɼ��������Դվ-(Required) 
	_TCHAR	GroupName[C_GROUPNAME_LEN];		//�ɼ��������Դ�����-(Optional)
	_TCHAR	SourceTag[C_SOURCETAG_LEN];		//�ɼ��������Դ���-(Optional)
	float 	UpperLimit;						//��������-(Optional, default = 0)
	float	LowerLimit;						//��������-(Optional, default = 0)
	WORD	PushReference;
	WORD	RuleReference;
	long	ExceptionMin;					//���ݴ�����̼��-��������, default = 1
	long	ExceptionMax;					//���ݴ��������, default = 1
	float 	ExceptionDev;					//���ݴ���������, default = 0
	WORD 	AlarmType;						//��������, default = 0
	WORD	AlarmState;
	float	AlarmHi;						//�߱���, default = 0
	float	AlarmLo;						//�ͱ���, default = 0
	float	AlarmHiHi;						//�߸߱���, default = 0
	float	AlarmLoLo;						//�͵ͱ���, default = 0
	WORD	HiPriority;						//�������ȼ�����ʱ������
	WORD	LoPriority;
	WORD	HiHiPriority;
	WORD	LoLoPriority;
	BYTE	IsArchived;						//�Ƿ�洢��ʷ����, default = 0
	BYTE	IsCompressed;					//�Ƿ������ʷѹ��, default = 1
	BYTE	InterMethod;					//��ʷ���ݵĲ�ֵ��ʽ(����/̨��)
	BYTE	Reserved2;
	long	HisIndex;
	long	CompressMin;					//ѹ����ϼ��
	long	CompressMax;					//ѹ������
	float	CompressDev;					//ѹ��������
	float	LastValue;						//�ϴ����ݴ浵��ֵ
	long	LastTimestamp;					//�ϴ����ݴ浵��ʱ��
	long	CreationDate;					//�ɼ��㴴������
}TAG_INFO;

typedef struct struValue{
	BYTE	Type;		// ����
	long	lTimestamp;
	union {				// ��ֵ				
		float	rval;						// ����	
		long	lval;						// ����
		BOOL	bval;						// ����
		_TCHAR	sval[C_STRINGVALUE_LEN];	// �ַ���
	};
}VALUE;

typedef struct struTagValue{
	_TCHAR	TagName[C_FULL_TAGNAME_LEN];
	long	Timestamp;		// ʱ���
	long	TagState;		// ״̬
	BYTE	TagType;		// ��ֵ����
	union {					// ��ֵ				
		float	rval;		// ����	
		long	lval;		// ����
		BOOL	bval;		// ����
		_TCHAR	sval[C_STRINGVALUE_LEN];	// �ַ���
	};
}TAGVAL, *LPTAGVAL;

enum Enum_Aggregate_Function 
{
	AF_SUMMARY,
	AF_MINIMUM,
	AF_MAXIMUM,
	AF_AVERAGE,
	AF_COUNT,
	AF_SUMMARY_FOR_CONTINOUS,
	AF_AVERAGE_FOR_CONTINOUS,
};

//handle to the recordset, forward only
#define HRECORDSET		long	


//wk, 2005.10.20, add:
#ifdef __cplusplus


//********* AGCN - AGILOR CONNECTION FUNCTIONS ***********
//--------------------------------------------------------

//this function must be executed before other functions
extern "C" BOOL PASCAL EXPORT Agcn_Startup();

//before connect to an agilor server, a server node must be created
//parameter 1 - named the agilor server, must be unique on local machine
//parameter 2 - handle to a window, be notified when sub data arrival or disconnected
//parameter 3 - a threadid which indicates this thread care for the related events
//parameter 4 - if allow named events, signaled when sub data arrival or disconnected
extern "C" BOOL PASCAL EXPORT Agcn_CreateNode
(LPCTSTR szServerName, HWND hWnd = NULL, DWORD hThreadID = NULL, BOOL bAllowEvents=FALSE);

//connect to specific agilor server node, which must be created by agcn_createnode
//return  0 : connection be created successfully
//return -1 : the server node hasn't been created
//return -2 : the server node has been connected
//return -3 : failed to connect, maybe the server is down or refused
//return -4 : timeout when attempt to connect the agilor server
//return -5 : socket error, socket error code is returned as negative
extern "C" long PASCAL EXPORT Agcn_Connect
(LPCTSTR szServerName, LPCTSTR szServerAddr, LPCTSTR szUserName, LPCTSTR szPassword, UINT nPort = 900);

extern "C" long PASCAL EXPORT Agcn_ConnectForDI
(LPCTSTR szServerName, LPCTSTR szServerAddr, LPCTSTR szUserName, LPCTSTR szPassword, UINT nPort = 900);

//disconnect from specific agilor server
//return  0 : disconnect successfully
//return -1 : the specific server is nonexistent
//return -2 : connection with the specific server has been closed
extern "C" long PASCAL EXPORT Agcn_Disconnect(LPCTSTR szServerName);

//enumerate the server nodes, which has been created 
//if return ture, lpSvrInfo pointers to a valid struct containing related information
//nServerID = 0 indicates the start of a new iterative process
extern "C" BOOL PASCAL EXPORT Agcn_EnumNodeInfo(long * nServerID, SERVER_INFO * pSvrInfo);

//when a server is used no longer, must be removed to free related resources
extern "C" BOOL PASCAL EXPORT Agcn_RemoveNode(LPCTSTR szServerName);

//before close application, clean up the resources used in the library
extern "C" BOOL PASCAL EXPORT Agcn_Cleanup();

//*********************** AGILOR DATA **********************

//subscribe real-time values of some tags
//sztagnames must be defined as [nTagCount][C_TAGNAME_LEN]
extern "C" long PASCAL EXPORT Agda_SubscribeTags
(LPCTSTR szServerName, LPCTSTR szTagNames, UINT nTagCount);

//cancel some subscription on specific tags
extern "C" long PASCAL EXPORT Agda_UnSubscribeTags
(LPCTSTR szServerName, LPCTSTR szTagNames, UINT nTagCount);

//cancel all subscription on specific server node
extern "C" long PASCAL EXPORT Agda_UnSubscribeAll(LPCTSTR szServerName);

//when notified on sub data arrival, call this funtion to get the data
extern "C" BOOL PASCAL EXPORT Agda_GetSubTagValue(TAGVAL * pTagVal);

//query real-time values of some tags
//sztagnames must be defined as [nTagCount][C_TAGNAME_LEN]
extern "C" HRECORDSET PASCAL EXPORT Agda_QuerySnapshots
(LPCTSTR szServerName, LPCTSTR szTagNames, UINT nTagCount);

//query a series history value of specific tag
//szfulltagname named as servername.tagname
extern "C" HRECORDSET PASCAL EXPORT Agda_QueryTagHistory
(LPCTSTR szFullTagName, long nStartTime, long nEndTime, long nStep=0);

extern "C" HRECORDSET PASCAL EXPORT Agda_QueryMultiTagHistory
(LPCTSTR szServerName, LPCTSTR szTagNames, long lTagCount, long nStartTime, long nEndTime, long nStep=0);

extern "C" long PASCAL EXPORT Agda_QueryTagHisStatistic
(LPCTSTR szFullTagName, long nStartTime, long nEndTime, long lStatisticType, TAGVAL * pTagVal);

//this function is used to get the results of querysnapshots or querytaghistory
extern "C" BOOL PASCAL EXPORT Agda_GetNextTagValue
(HRECORDSET hRecordset, TAGVAL * pTagVal, BOOL bRemoved=TRUE);

//aggregate funtion on a series history value of specific tag
//wherein szfulltagname named as servername.tagname
extern "C" long PASCAL EXPORT Agda_GetAggregateValue
(HRECORDSET hRecordset, TAGVAL * pTagVal, long nAFunction=AF_SUMMARY, BOOL bRemoved=TRUE);

//set a value to specific tag
extern "C" long PASCAL EXPORT Agda_SetTagValue
(LPCTSTR szFullTagName, VALUE * pValue, BOOL bManual = FALSE, LPCTSTR szComment = NULL);

//add comment to a specifc tag state on specific time
extern "C" long PASCAL EXPORT Agda_AddTagComment
(LPCTSTR szFullTagName, long nTimeStamp, long nTagState, LPCTSTR szComment);

//*********************** AGILOR POINT **********************

//remove tag from server
extern "C" long PASCAL EXPORT Agpt_RemoveTag
(LPCTSTR szServerName, long lTagID);

//add new tag to server
extern "C" long PASCAL EXPORT Agpt_AddNewTag
(LPCTSTR szServerName, TAG_NODE* pTagNode, BOOL bOverwrite = TRUE);

//retrieve devices information on specific server
extern "C" HRECORDSET PASCAL EXPORT Agpt_QueryDeviceInfo(LPCTSTR szServerName);

//enumerate the device information returned by querydeviceinfo
//nDeviceID must better be set to zero at beginning
extern "C" BOOL PASCAL EXPORT Agpt_EnumDeviceInfo
(HRECORDSET hRecordset, long * nDeviceID, DEV_INFO * pDevInfo);

//query all tags on specific device on specific server
extern "C" HRECORDSET PASCAL EXPORT Agpt_QueryTagsbyDevice
(LPCTSTR szServerName, LPCTSTR szDeviceName);

//query tags by namemask such as "LH*" on specific server
extern "C" HRECORDSET PASCAL EXPORT Agpt_QueryTagsbyNameMask
(LPCTSTR szServerName, LPCTSTR szTagNameMask);

//enumerate the tagname returned by querytags
extern "C" BOOL PASCAL EXPORT Agpt_EnumTagName
(HRECORDSET hRecordset, long * nTagID, LPTSTR szTagName);

//retrieve detailed information of specific tag
extern "C" long PASCAL EXPORT Agpt_GetTagInfo
(LPCTSTR szFullTagName, TAG_INFO * pTagInfo);

//********************** AGILOR TIME ***********************

//convert time to a long integer as second count since 1970.1.1
extern "C" long PASCAL EXPORT Agtm_DateTime2Long
(int hour, int min, int sec, int year, int mon, int mday);

//only local time is supported at present
extern "C" long PASCAL EXPORT Agtm_GetCurrTime(BOOL bLocal=TRUE);

//convert the long time to YYYY-MM-DD HH:MM:SS
extern "C" long PASCAL EXPORT Agtm_Long2DateString
(long nDateTime, LPTSTR szDateString);

extern "C" BOOL PASCAL EXPORT Agpt_GetTagNamebyID
(LPSTR szServerName, long nTagID, LPTSTR szTagName);

extern "C" long PASCAL EXPORT Agcn_GetServerTime
(LPCTSTR szServerName, long* plServerTime);

extern "C" BOOL PASCAL EXPORT Agpt_TagExist
(LPTSTR szFullTagName);

extern "C" BOOL PASCAL EXPORT Agda_CloseRecordset
(HRECORDSET hRecordset);

/////////��������Ӧ�õķ��ʽӿ�

extern "C" HRECORDSET PASCAL EXPORT Agda_Wea_QueryMultiTagHistory
(LPCTSTR szServerName, LPCTSTR szStationNames, LPCTSTR szElementNames, long nStartTime, long nEndTime);

extern "C" HRECORDSET PASCAL EXPORT Agda_Wea_QueryMultiTagHistoryWithCondition
(LPCTSTR szServerName, LPCTSTR szStationNames, LPCTSTR szElementNames, long nStartTime, long nEndTime, LPCTSTR szCondition = NULL);

extern "C" long PASCAL EXPORT Agda_Wea_CloseRecordset
(HRECORDSET hRecordset);

extern "C"  long PASCAL EXPORT Agda_Wea_MoveFirst
(HRECORDSET hRecordset);

extern "C"  long PASCAL EXPORT Agda_Wea_MoveTo
(HRECORDSET hRecordset, long lRowOffset);

extern "C"  long PASCAL EXPORT Agda_Wea_IsEOF
(HRECORDSET hRecordset);

extern "C"  long PASCAL EXPORT Agda_Wea_MoveNext
(HRECORDSET hRecordset);

extern "C"  long PASCAL EXPORT Agda_Wea_GetRowAmount
(HRECORDSET hRecordset);

extern "C"  long PASCAL EXPORT Agda_Wea_GetStationName
(HRECORDSET hRecordset, char* sStationName);

extern "C"  long PASCAL EXPORT Agda_Wea_GetTimestamp
(HRECORDSET hRecordset, long* lTimestamp);

extern "C"  long PASCAL EXPORT Agda_Wea_GetElementLongValue
(HRECORDSET hRecordset, long lElementIndex, long* pLongValue);

extern "C"  long PASCAL EXPORT Agda_Wea_GetElementFloatValue
(HRECORDSET hRecordset, long lElementIndex, float* pFloatValue);

extern "C" long PASCAL EXPORT Agda_Wea_GetElementStringValue
(HRECORDSET hRecordset, long lElementIndex, char* sStringValue);

extern "C" long PASCAL EXPORT Agda_Wea_GetElementTimeValue
(HRECORDSET hRecordset, long lElementIndex, char* sFormat, char* sTimeString);

extern "C" long PASCAL EXPORT Agda_SetTagValues
(LPCTSTR szFullTagNames, VALUE * pValues, long nTagCount, BOOL bManual, LPCTSTR szComment);

//**********************************************************
//----------------------------------------------------------

//wk, 2005.10.20, add:
#endif


//wk, 2005.10.20, add ->

#ifndef __cplusplus

//********* AGCN - AGILOR CONNECTION FUNCTIONS ***********
//--------------------------------------------------------

//this function must be executed before other functions
BOOL PASCAL EXPORT Agcn_Startup();

//before connect to an agilor server, a server node must be created
//parameter 1 - named the agilor server, must be unique on local machine
//parameter 2 - handle to a window, be notified when sub data arrival or disconnected
//parameter 3 - a threadid which indicates this thread care for the related events
//parameter 4 - if allow named events, signaled when sub data arrival or disconnected
BOOL PASCAL EXPORT Agcn_CreateNode
(LPCTSTR szServerName, HWND hWnd, DWORD hThreadID, BOOL bAllowEvents);

//connect to specific agilor server node, which must be created by agcn_createnode
//return  0 : connection be created successfully
//return -1 : the server node hasn't been created
//return -2 : the server node has been connected
//return -3 : failed to connect, maybe the server is down or refused
//return -4 : timeout when attempt to connect the agilor server
//return -5 : socket error, socket error code is returned as negative
long PASCAL EXPORT Agcn_Connect
(LPCTSTR szServerName, LPCTSTR szServerAddr, LPCTSTR szUserName, LPCTSTR szPassword, UINT nPort);
long PASCAL EXPORT Agcn_ConnectForDI
(LPCTSTR szServerName, LPCTSTR szServerAddr, LPCTSTR szUserName, LPCTSTR szPassword, UINT nPort);

//disconnect from specific agilor server
//return  0 : disconnect successfully
//return -1 : the specific server is nonexistent
//return -2 : connection with the specific server has been closed
long PASCAL EXPORT Agcn_Disconnect(LPCTSTR szServerName);

//enumerate the server nodes, which has been created 
//if return ture, lpSvrInfo pointers to a valid struct containing related information
//nServerID = 0 indicates the start of a new iterative process
BOOL PASCAL EXPORT Agcn_EnumNodeInfo(long * nServerID, SERVER_INFO * pSvrInfo);

//when a server is used no longer, must be removed to free related resources
BOOL PASCAL EXPORT Agcn_RemoveNode(LPCTSTR szServerName);

//before close application, clean up the resources used in the library
BOOL PASCAL EXPORT Agcn_Cleanup();

//*********************** AGILOR DATA **********************

//subscribe real-time values of some tags
//sztagnames must be defined as [nTagCount][C_TAGNAME_LEN]
long PASCAL EXPORT Agda_SubscribeTags
(LPCTSTR szServerName, LPCTSTR szTagNames, UINT nTagCount);

//cancel some subscription on specific tags
long PASCAL EXPORT Agda_UnSubscribeTags
(LPCTSTR szServerName, LPCTSTR szTagNames, UINT nTagCount);

//cancel all subscription on specific server node
long PASCAL EXPORT Agda_UnSubscribeAll(LPCTSTR szServerName);

//when notified on sub data arrival, call this funtion to get the data
BOOL PASCAL EXPORT Agda_GetSubTagValue(TAGVAL * pTagVal);

//query real-time values of some tags
//sztagnames must be defined as [nTagCount][C_TAGNAME_LEN]
HRECORDSET PASCAL EXPORT Agda_QuerySnapshots
(LPCTSTR szServerName, LPCTSTR szTagNames, UINT nTagCount);

//query a series history value of specific tag
//szfulltagname named as servername.tagname
HRECORDSET PASCAL EXPORT Agda_QueryTagHistory
(LPCTSTR szFullTagName, long nStartTime, long nEndTime, long nStep);

HRECORDSET PASCAL EXPORT Agda_QueryMultiTagHistory
(LPCTSTR szServerName, LPCTSTR szTagNames, long lTagCount, long nStartTime, long nEndTime, long nStep);

long PASCAL EXPORT Agda_QueryTagHisStatistic
(LPCTSTR szFullTagName, long nStartTime, long nEndTime, long lStatisticType, TAGVAL * pTagVal);

//this function is used to get the results of querysnapshots or querytaghistory
BOOL PASCAL EXPORT Agda_GetNextTagValue
(HRECORDSET hRecordset, TAGVAL * pTagVal, BOOL bRemoved);

//aggregate funtion on a series history value of specific tag
//wherein szfulltagname named as servername.tagname
long PASCAL EXPORT Agda_GetAggregateValue
(HRECORDSET hRecordset, TAGVAL * pTagVal, long nAFunction, BOOL bRemoved);

//set a value to specific tag
long PASCAL EXPORT Agda_SetTagValue
(LPCTSTR szFullTagName, VALUE * pValue, BOOL bManual, LPCTSTR szComment);

//add comment to a specifc tag state on specific time
long PASCAL EXPORT Agda_AddTagComment
(LPCTSTR szFullTagName, long nTimeStamp, long nTagState, LPCTSTR szComment);

//*********************** AGILOR POINT **********************

//remove tag from server
long PASCAL EXPORT Agpt_RemoveTag
(LPCTSTR szServerName, long lTagID);

//add new tag to server
long PASCAL EXPORT Agpt_AddNewTag
(LPCTSTR szServerName, TAG_NODE* pTagNode, BOOL bOverwrite);

//retrieve devices information on specific server
HRECORDSET PASCAL EXPORT Agpt_QueryDeviceInfo(LPCTSTR szServerName);

//enumerate the device information returned by querydeviceinfo
//nDeviceID must better be set to zero at beginning
BOOL PASCAL EXPORT Agpt_EnumDeviceInfo
(HRECORDSET hRecordset, long * nDeviceID, DEV_INFO * pDevInfo);

//query all tags on specific device on specific server
HRECORDSET PASCAL EXPORT Agpt_QueryTagsbyDevice
(LPCTSTR szServerName, LPCTSTR szDeviceName);

//query tags by namemask such as "LH*" on specific server
HRECORDSET PASCAL EXPORT Agpt_QueryTagsbyNameMask
(LPCTSTR szServerName, LPCTSTR szTagNameMask);

//enumerate the tagname returned by querytags
BOOL PASCAL EXPORT Agpt_EnumTagName
(HRECORDSET hRecordset, long * nTagID, LPTSTR szTagName);

//retrieve detailed information of specific tag
long PASCAL EXPORT Agpt_GetTagInfo
(LPCTSTR szFullTagName, TAG_INFO * pTagInfo);

//********************** AGILOR TIME ***********************

//convert time to a long integer as second count since 1970.1.1
long PASCAL EXPORT Agtm_DateTime2Long
(int hour, int min, int sec, int year, int mon, int mday);

//only local time is supported at present
long PASCAL EXPORT Agtm_GetCurrTime(BOOL bLocal);

//convert the long time to YYYY-MM-DD HH:MM:SS
long PASCAL EXPORT Agtm_Long2DateString
(long nDateTime, LPTSTR szDateString);

BOOL PASCAL EXPORT Agpt_GetTagNamebyID
(LPSTR szServerName, long nTagID, LPTSTR szTagName);

long PASCAL EXPORT Agcn_GetServerTime
(LPCTSTR szServerName, long* plServerTime);

BOOL PASCAL EXPORT Agpt_TagExist
(LPTSTR szFullTagName);

BOOL PASCAL EXPORT Agda_CloseRecordset
(HRECORDSET hRecordset);

/////////��������Ӧ�õķ��ʽӿ�

HRECORDSET PASCAL EXPORT Agda_Wea_QueryMultiTagHistory
(LPCTSTR szServerName, LPCTSTR szStationNames, LPCTSTR szElementNames, long nStartTime, long nEndTime);

HRECORDSET PASCAL EXPORT Agda_Wea_QueryMultiTagHistoryWithCondition
(LPCTSTR szServerName, LPCTSTR szStationNames, LPCTSTR szElementNames, long nStartTime, long nEndTime, LPCTSTR szCondition = NULL)

long PASCAL EXPORT Agda_Wea_CloseRecordset
(HRECORDSET hRecordset);

long PASCAL EXPORT Agda_Wea_MoveFirst
(HRECORDSET hRecordset);

long PASCAL EXPORT Agda_Wea_MoveTo
(HRECORDSET hRecordset, long lRowOffset);

long PASCAL EXPORT Agda_Wea_IsEOF
(HRECORDSET hRecordset);

long PASCAL EXPORT Agda_Wea_MoveNext
(HRECORDSET hRecordset);

long PASCAL EXPORT Agda_Wea_GetRowAmount
(HRECORDSET hRecordset);

long PASCAL EXPORT Agda_Wea_GetStationName
(HRECORDSET hRecordset, char* sStationName);

long PASCAL EXPORT Agda_Wea_GetTimestamp
(HRECORDSET hRecordset, long* lTimestamp);

long PASCAL EXPORT Agda_Wea_GetElementLongValue
(HRECORDSET hRecordset, long lElementIndex, long* pLongValue);

long PASCAL EXPORT Agda_Wea_GetElementFloatValue
(HRECORDSET hRecordset, long lElementIndex, float* pFloatValue);

long PASCAL EXPORT Agda_Wea_GetElementStringValue
(HRECORDSET hRecordset, long lElementIndex, char* sStringValue);

long PASCAL EXPORT Agda_Wea_GetElementTimeValue
(HRECORDSET hRecordset, long lElementIndex, char* sFormat, char* sTimeString);

long PASCAL EXPORT Agda_SetTagValues
(LPCTSTR szFullTagNames, VALUE * pValues, long nTagCount, BOOL bManual, LPCTSTR szComment);

//**********************************************************
//----------------------------------------------------------

#endif

//<- wk, 2005.10.20, add


#ifdef __cplusplus
   }
#endif

#endif	//_AGILOR_CALL_INTERFACE_H_