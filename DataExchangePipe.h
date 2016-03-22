// DataExchangePipe.h: interface for the CDataExchangePipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAEXCHANGEPIPE_H__FAA2F47E_5211_449D_A351_7E40AABB57D7__INCLUDED_)
#define AFX_DATAEXCHANGEPIPE_H__FAA2F47E_5211_449D_A351_7E40AABB57D7__INCLUDED_

#define DATA_EXCHANGE_BLOCK_SIZE					10240

typedef struct structDataExchangeBlock
{
	WORD wDataLen;
	BYTE lpData[DATA_EXCHANGE_BLOCK_SIZE];
}DataExchangeBlock;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataExchangePipe : public CBaseObject
{
public:
	CDataExchangePipe(long lDataBufferCount = 10000);
	virtual ~CDataExchangePipe();

public:
	BOOL MultiPut(void* pData, WORD wDataLen, DWORD nTimeOut = 10, BOOL bNotifyImmediate = TRUE);
	BOOL PutDataEx(void* pData, WORD wDataLen, DWORD nTimeOut = 10, BOOL bNotifyImmediate = TRUE);
	void ClearData();
	DataExchangeBlock* GetDataExchangeBlock(DWORD nTimeOut = 10);
	DataExchangeBlock** m_ppDataBuffers;
	void* m_pBuffer;

protected:
	void UnlockPut();
	void LockPut();
	BOOL PutData(void* pData, WORD wDataLen, DWORD nTimeOut = 0, BOOL bNotifyImmediate = TRUE);
	HANDLE m_hDataArriveEvent;//缓冲区是否已空，阻塞取数进程
	HANDLE m_hDataBufferAvailableEvent;//缓冲区是否满，阻塞读数进程
	CRITICAL_SECTION m_PutCriticalSection;
	long m_lDataBufferCount; //发送块指针，取数时将m_lFirstIndex数据块内容指向m_lDataBufferCount
	long m_lFirstIndex;//取数队列头指针，仅在取数进程中修改
	long m_lCurrentIndex;//放数队列头指针，在顺时针方向（0->9）m_lCurrentIndex要大于m_lFirstIndex

};

#endif // !defined(AFX_DATAEXCHANGEPIPE_H__FAA2F47E_5211_449D_A351_7E40AABB57D7__INCLUDED_)
