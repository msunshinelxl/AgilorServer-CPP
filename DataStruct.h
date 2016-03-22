#ifndef __DATASTRUCT_H__	
#define __DATASTRUCT_H__

#define NAME_LENGTH 64
#define STRING_VALUE_LEN 128

#define START_COMMAND				0
#define ADD_PARAMETER_COMMAND		1
#define END_COMMAND					2
#define WRITE_PARAMETER_COMMAND		3
#define UPDATE_DA_RATE_COMMAND		4

#define COMM_INT8 8
#define COMM_INT16 16
#define COMM_INT32 32
#define COMM_INT64 64
#define COMM_BOOL 'B'
#define COMM_FLOAT 'F'
#define COMM_DOUBLE 'D'
#define COMM_STRUCT 'T'
#define COMM_ARRAY 'A'
#define COMM_STRING 'S'
#define COMM_HEAD_SIZE 5
#include "ACI_H.h"
struct Monitor_Info {
	char name[NAME_LENGTH];
	int tagid;
	unsigned int timeStamp;
	char type;
	union{
		long lval;
		float rval;
		bool bval;
		char sval[STRING_VALUE_LEN];
	};
};

struct Command_Info {
	int command_id;
	char szParamName[64];
	int tagid;
	char type;
	union{
		long lval;
		float rval;
		bool bval;
		char sval[STRING_VALUE_LEN];
	};
};

enum COMM_TYPE
{
	COMM_ADD_TAG=1,
	COMM_ADD_VALUE,
	COMM_GET_VALUE,
	COMM_GET_ALL_TAG,
	COMM_PING,
};
enum RES_TYPE
{
	RES_OK=0,
	RES_FAIL_COMMON,
	RES_FAIL_NO_TAG,
	RES_FAIL_RETURN_EMPTY,
};


struct COMM_Head {
	byte type;
	int len;
};
// --- jwj ---
struct RealTimeData_ADDPARAM {
	byte type;
	byte len;
	//char* sval;
};
// --- jwj ---

struct RealTimeData_L {
	byte type;
	byte len;
	char deviceName[C_DEVICENAME_LEN];
	char tagSourceName[C_SOURCETAG_LEN];
	int timestamp;
	int lval;
};

struct RealTimeData_R {
	byte type;
	byte len;
	char deviceName[C_DEVICENAME_LEN];
	char tagSourceName[C_SOURCETAG_LEN];
	int timestamp;
	float fval;
};

struct RealTimeData_B {
	byte type;
	byte len;
	char deviceName[C_DEVICENAME_LEN];
	char tagSourceName[C_SOURCETAG_LEN];
	int timestamp;
	byte bval;
};

struct RealTimeData_S {
	byte type;
	byte len;
	char deviceName[C_DEVICENAME_LEN];
	char tagSourceName[C_SOURCETAG_LEN];
	int timestamp;
	//char* sval;
};



#endif