#include "StdAfx.h"
#include "DoubleQueueBuffer.h"

DQBDataExchangeBlock::DQBDataExchangeBlock(int size):maxSize(size){
	lpData=(BYTE *)malloc(sizeof(BYTE)*size);
	wDataLen=0;
}
DQBDataExchangeBlock::~DQBDataExchangeBlock(){
	free(lpData);
}

DoubleQueueBuffer::DoubleQueueBuffer(int minSize,int maxSize)
	:CBaseObject(),consumerQueue(),producerQueue(),minBufferSize(minSize),maxBufferSize(maxSize)
{
	currentBufferSize =minSize;
	DQBDataExchangeBlock * tmpBuf=new DQBDataExchangeBlock();
	swapBuffer=tmpBuf;
	for (int i=0;i<minSize;i++)
	{
		producerQueue.push(new DQBDataExchangeBlock());
	}
	m_hDataArriveEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hDataBufferAvailableEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
}

DoubleQueueBuffer::~DoubleQueueBuffer(void)
{
	while(producerQueue.empty()==FALSE){
		delete(producerQueue.front());
		producerQueue.pop();
	}
	while(consumerQueue.empty()==FALSE){
		delete(consumerQueue.front());
		consumerQueue.pop();
	}
	CloseHandle(m_hDataArriveEvent);
	CloseHandle(m_hDataBufferAvailableEvent);
}


void DoubleQueueBuffer::ClearProducerBlock(){
	int i=0;
	for(i=0;i<currentBufferSize/2&&currentBufferSize-i>=minBufferSize;i++){
		delete(producerQueue.front());
		producerQueue.pop();
	}
	currentBufferSize-=i;
}


DQBDataExchangeBlock * DoubleQueueBuffer::GetData(DWORD timeOut){//多进程取数不安全，因为swapBuffer可能被清除，但是把数据拷贝工作从临界区内剔除，有效提高效率
	if(timeOut>0)
		WaitForSingleObject(m_hDataArriveEvent,timeOut);
	Lock();
	if(consumerQueue.size()==0){
		if(producerQueue.front()->wDataLen==0){
			ClearProducerBlock();
			ResetEvent(m_hDataArriveEvent);
			Unlock();
			return NULL;
		}else{
			consumerQueue.push(producerQueue.front());
			producerQueue.pop();
		}
	}
	(swapBuffer)->wDataLen=0;
	producerQueue.push(swapBuffer);
	DQBDataExchangeBlock * tmp=consumerQueue.front();
	consumerQueue.pop();
	swapBuffer=tmp;
	if(consumerQueue.size()==0){
		if(producerQueue.front()->wDataLen==0){
			ClearProducerBlock();
			ResetEvent(m_hDataArriveEvent);
		}
		else{
			consumerQueue.push(producerQueue.front());
			producerQueue.pop();
		}
	}
	SetEvent(m_hDataBufferAvailableEvent);
	Unlock();
	return swapBuffer;
}

DQBDataExchangeBlock* DoubleQueueBuffer::GetProducerBlock(){
	if(producerQueue.size()==0){
		if(currentBufferSize<maxBufferSize){
			int i=0;
			for(i=0;i<currentBufferSize&&currentBufferSize+i<maxBufferSize;i++){
				producerQueue.push(new DQBDataExchangeBlock());
			}
			currentBufferSize+=i;
		}else{
			return NULL;
		}
	}
	return producerQueue.front();
}

BOOL DoubleQueueBuffer::PutData(void* pData, WORD wDataLen, DWORD timeOut, BOOL bNotifyImmediate){
	if(timeOut>0)
		WaitForSingleObject(m_hDataBufferAvailableEvent,timeOut);
	Lock();
	DQBDataExchangeBlock * tmpBlock=this->GetProducerBlock();
	if(tmpBlock==NULL){
		ResetEvent(m_hDataBufferAvailableEvent);
		Unlock();
		return FALSE;
	}
	DQBDataExchangeBlock ** currentBlock=&(tmpBlock);
	if((*currentBlock)->wDataLen + wDataLen > (*currentBlock)->maxSize){
		consumerQueue.push(*currentBlock);
		producerQueue.pop();
		SetEvent(m_hDataArriveEvent);
		tmpBlock=this->GetProducerBlock();
		if(tmpBlock==NULL){
			ResetEvent(m_hDataBufferAvailableEvent);
			Unlock();
			return FALSE;
		}
		currentBlock=&tmpBlock;
	}
	memcpy((*currentBlock)->lpData +(*currentBlock)->wDataLen, pData, wDataLen);
	(*currentBlock)->wDataLen += wDataLen;
	if(bNotifyImmediate){
		consumerQueue.push(*currentBlock);
		producerQueue.pop();
		SetEvent(m_hDataArriveEvent);
	}
	Unlock();
	return TRUE;
}
