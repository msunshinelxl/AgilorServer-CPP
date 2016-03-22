// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4C354B20_8A9B_4F80_9A49_6C3FC5AB8F9A__INCLUDED_)
#define AFX_STDAFX_H__4C354B20_8A9B_4F80_9A49_6C3FC5AB8F9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define INI_FILE_PATH		"D:\\ReceiveServerSetting.ini"
#define LOG_FILE_PATH		"D:\\log_server_rtdb.txt" // runtime_rtdb_log
#define LOG_PROPERTY        "D:\\log4cxx.properties"
#define LOG_LOGGER_NAME     "Agilor"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define DEBUG_MODE

#include <winsock2.h>
#include <map>


#include "share.h"
#include <string.h>
#include "devicertdbapi.h"
#include "globaldefinitions.h"
#include "datastruct.h"
#include "baseobject.h"
#include "dataexchangepipe.h"
#include "basethread.h"
#include "basesocketsendthread.h"
#include "basesocketreceivethread.h"
#include "basesocket.h"
#include "monitorreceivesocket.h"
#include "listensocket.h"
#include "aci_h.h"
#include "resource.h"

#include "mysql.h"
#include "KernelMonitorv1Dlg.h"
#include "string.h"
#include "BaseType.h"
#include "BaseGetValueEntity.h"
#include "DataExecutor.h"
#include "MonitorReceiveSocket.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4C354B20_8A9B_4F80_9A49_6C3FC5AB8F9A__INCLUDED_)
#include <vector>

#include <log4cxx/logstring.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <locale.h>
#include <log4cxx/basicconfigurator.h>

//#pragma comment(lib, "log4cxx.lib")


using namespace std;
using namespace log4cxx;
using namespace log4cxx::helpers;


extern vector<string> strSplit(string source,CString splitItem);
extern bool inStringArray(vector<string> stringArray,string item);
extern void initTagVal(TAG_NODE& data);
//extern void parseBaseToken(BaseType* res,int *st,int ed,char *data);
extern int byte2Int(char*);
//extern bool parseValue(byte *type,BaseType* res,char *data);
extern void getTagValueFromBaseType(TAG_VALUE_LOCAL &dist,BaseType src,char type);
extern void intToByte4J(int i,byte *bytes,int size = 4);
extern long time2Long(char *time);
extern char *myStrCat(char ** strs,int num);