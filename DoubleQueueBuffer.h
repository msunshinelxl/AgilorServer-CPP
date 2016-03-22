#pragma once
#include <queue>
#include "BaseObject.h"
using namespace std;

#define DATA_EXCHANGE_BLOCK_SIZE					10240
class DQBDataExchangeBlock
{
public:
	DQBDataExchangeBlock(int size=DATA_EXCHANGE_BLOCK_SIZE);
	WORD wDataLen;
	const WORD maxSize;
	virtual ~DQBDataExchangeBlock();
	BYTE* lpData;
};
class DoubleQueueBuffer:public CBaseObject
{
public:
	DoubleQueueBuffer(int minBufferSize=10,int maxBufferSize=10000);
	DQBDataExchangeBlock *GetData(DWORD timeOut=10);
	BOOL PutData(void* pData, WORD wDataLen, DWORD nTimeOut = 10, BOOL bNotifyImmediate = TRUE);
	virtual ~DoubleQueueBuffer(void);


	int currentBufferSize;
private:
	queue<DQBDataExchangeBlock*> consumerQueue;
	queue<DQBDataExchangeBlock*> producerQueue;
	DQBDataExchangeBlock* swapBuffer;
	HANDLE m_hDataArriveEvent;
	HANDLE m_hDataBufferAvailableEvent;

	const int minBufferSize;
	const int maxBufferSize;
	
	void ClearProducerBlock();
	DQBDataExchangeBlock* GetProducerBlock();
};
