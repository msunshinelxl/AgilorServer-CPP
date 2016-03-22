// DataExchangePipe.cpp: implementation of the CDataExchangePipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataExchangePipe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataExchangePipe::CDataExchangePipe(long lDataBufferCount)
{
	m_lDataBufferCount = lDataBufferCount;
	m_pBuffer = malloc(sizeof(DataExchangeBlock) * (m_lDataBufferCount + 1));
	m_ppDataBuffers = (DataExchangeBlock**)malloc(sizeof(DataExchangeBlock*) * (m_lDataBufferCount + 1));
	m_ppDataBuffers[0] = (DataExchangeBlock*)m_pBuffer;
	for (int i=1;i<=m_lDataBufferCount;i++)
	{
		m_ppDataBuffers[i] = m_ppDataBuffers[i-1] + 1;
		m_ppDataBuffers[i]->wDataLen = 0;
	}
	m_hDataArriveEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hDataBufferAvailableEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_lFirstIndex = 0;
	m_lCurrentIndex = 0;
	m_ppDataBuffers[m_lCurrentIndex]->wDataLen = 0;
	::InitializeCriticalSection(&m_PutCriticalSection);
}

CDataExchangePipe::~CDataExchangePipe()
{
	free(m_pBuffer);
	free(m_ppDataBuffers);
	CloseHandle(m_hDataArriveEvent);
	CloseHandle(m_hDataBufferAvailableEvent);
	::DeleteCriticalSection(&m_PutCriticalSection);
}

DataExchangeBlock* CDataExchangePipe::GetDataExchangeBlock(DWORD nTimeOut)
{
	WaitForSingleObject(m_hDataArriveEvent, nTimeOut);
	Lock();
	if (m_ppDataBuffers[m_lFirstIndex]->wDataLen == 0)
	{
		ResetEvent(m_hDataArriveEvent);
		Unlock();
		return NULL;
	}
	
	DataExchangeBlock* p;
	m_ppDataBuffers[m_lDataBufferCount]->wDataLen = 0;
	p = m_ppDataBuffers[m_lFirstIndex];
	m_ppDataBuffers[m_lFirstIndex] = m_ppDataBuffers[m_lDataBufferCount];
	m_ppDataBuffers[m_lDataBufferCount] = p;
	if (m_lCurrentIndex == m_lFirstIndex)//数据取空，阻塞GetDataExchangeBlock函数
	{
		m_lCurrentIndex = 0;
		m_lFirstIndex = 0;
		ResetEvent(m_hDataArriveEvent);
	}
	else
	{
		m_lFirstIndex = (m_lFirstIndex + 1) % m_lDataBufferCount;
	}
	SetEvent(m_hDataBufferAvailableEvent);
	Unlock();
	return m_ppDataBuffers[m_lDataBufferCount];
}

BOOL CDataExchangePipe::PutData(void *pData, WORD wDataLen, DWORD nTimeOut, BOOL bNotifyImmediate)
{
	if (nTimeOut > 0)
	{
		WaitForSingleObject(m_hDataBufferAvailableEvent, nTimeOut);
	}
	Lock();
	if (m_ppDataBuffers[m_lCurrentIndex]->wDataLen + wDataLen > DATA_EXCHANGE_BLOCK_SIZE)//判断[m_lCurrentIndex]对应的当前数据块大小剩余空间是否够大，可放数据
	{
		//空间不够大，通知GetDataExchangeBlock取数
		SetEvent(m_hDataArriveEvent);
		if ((m_lCurrentIndex + 1) % m_lDataBufferCount == m_lFirstIndex)
		{
			//所有数据块都写满，等待
			ResetEvent(m_hDataBufferAvailableEvent);
			Unlock();
			return FALSE;
		}
		else
		{
			//找到空余数据块
			m_lCurrentIndex = (m_lCurrentIndex + 1) % m_lDataBufferCount;
		}
	}
	memcpy(m_ppDataBuffers[m_lCurrentIndex]->lpData + m_ppDataBuffers[m_lCurrentIndex]->wDataLen, pData, wDataLen);
	m_ppDataBuffers[m_lCurrentIndex]->wDataLen += wDataLen;
	if (bNotifyImmediate)
	{
		//SetEvent(m_hDataArriveEvent);
	}
	Unlock();
	return TRUE;
}

void CDataExchangePipe::ClearData()
{
	Lock();
	m_lFirstIndex = 0;
	m_lCurrentIndex = 0;
	m_ppDataBuffers[m_lCurrentIndex]->wDataLen = 0;
	ResetEvent(m_hDataArriveEvent);
	SetEvent(m_hDataBufferAvailableEvent);
	Unlock();
}

BOOL CDataExchangePipe::PutDataEx(void *pData, WORD wDataLen, DWORD nTimeOut, BOOL bNotifyImmediate)
{
	if (PutData(pData, wDataLen, 0, bNotifyImmediate))
	{
		return TRUE;
	}
	else
	{
		if (PutData(pData, wDataLen, nTimeOut, bNotifyImmediate))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

void CDataExchangePipe::LockPut()
{
	EnterCriticalSection(&m_PutCriticalSection);
}

void CDataExchangePipe::UnlockPut()
{
	LeaveCriticalSection(&m_PutCriticalSection);
}

BOOL CDataExchangePipe::MultiPut(void *pData, WORD wDataLen, DWORD nTimeOut, BOOL bNotifyImmediate)
{
	LockPut();
	if (PutData(pData, wDataLen, 0, bNotifyImmediate))
	{
		UnlockPut();
		return TRUE;
	}
	else
	{
		if (PutData(pData, wDataLen, nTimeOut, bNotifyImmediate))
		{
			UnlockPut();
			return TRUE;
		}
		else
		{
			UnlockPut();
			return FALSE;
		}
	}
}
