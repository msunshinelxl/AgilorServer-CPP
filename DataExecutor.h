#pragma once

class DataExecutor:public CBaseThread
{
DECLARE_DYNCREATE(DataExecutor)

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	void SetSocket(CMonitorReceiveSocket* pSocket);
	void DataExecutor::MyPutData(byte* data,int length);
protected: 
	DataExecutor();
	~DataExecutor();
	int ParesData(int);
	void ParsePackage();
	CMonitorReceiveSocket * recvSocket;
	char m_pParseBuffer[SOCKET_BUFFER_SIZE*5];
	int m_lPos;
	DECLARE_MESSAGE_MAP()
};

