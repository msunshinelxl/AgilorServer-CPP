#include "stdafx.h"
#include "DataExecutor.h"

IMPLEMENT_DYNCREATE(DataExecutor, CBaseThread)
DataExecutor::DataExecutor()
{
	recvSocket=NULL;
	m_lPos=0;
	this->m_bAutoDelete=true;
}

BOOL DataExecutor::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	while (recvSocket == NULL)
		Sleep(1);

	return CBaseThread::InitInstance();
}

int DataExecutor::ParesData(int ntimeOut){

	DQBDataExchangeBlock* tmp=recvSocket->recvBuffer->GetData(ntimeOut);
	if(tmp!=NULL){
		memcpy( m_pParseBuffer + m_lPos,tmp->lpData,tmp->wDataLen);
		m_lPos += tmp->wDataLen;
		ParsePackage();
	}
	return 0;
}
void DataExecutor::MyPutData(byte* data,int length){
	int tmpST=length;
	do{
		this->recvSocket->PutData(data+length-tmpST,tmpST>=DATA_EXCHANGE_BLOCK_SIZE?DATA_EXCHANGE_BLOCK_SIZE:tmpST);
		tmpST-=DATA_EXCHANGE_BLOCK_SIZE;
	}while(tmpST>0);
}

void DataExecutor::ParsePackage()
{
	BOOL bExit = FALSE;
	int iParsePos = 0;
	// struct Monitor_Info* temp;
	TAG_VALUE_LOCAL tagvalue;
	TAG_NODE tagNode;
	TAGVAL tv;
	TAG_INFO ti;
	long result=0;
	COMM_Head* pHead = NULL;
	LPSTR deviceName;
	int PHLength=0;
	LoggerPtr logger(Logger::getLogger(LOG_LOGGER_NAME));
	BaseType *baseType=new BaseType();
	BaseGetValueEntity *bgve=new BaseGetValueEntity();
	do
	{
		if ((m_lPos - iParsePos) <COMM_HEAD_SIZE)
		{
			bExit = TRUE;
		}
		else
		{
			pHead =(COMM_Head*)(m_pParseBuffer+iParsePos);
			PHLength=byte2Int(m_pParseBuffer+iParsePos+1)+COMM_HEAD_SIZE;//byte2Int(m_pParseBuffer+iParsePos+1)+5;
			if ((m_lPos - iParsePos) < PHLength)
			{
				bExit = TRUE;
			}
			else
			{
				memset(&tagvalue,0,sizeof(TAG_VALUE_LOCAL));
				//baseType->free();
				memset(baseType,0,sizeof(BaseType));
				switch(pHead->type)	// *(m_pBuffer + iParsePos)
				{
					case COMM_ADD_TAG:
						{
							int st=iParsePos;
							initTagVal(tagNode);
							st+=COMM_HEAD_SIZE;
							//init name sourcetag
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							strcpy(tagNode.sourcetag,(char*)(baseType->pv));
							strcpy(tagNode.name,(char*)(baseType->pv));
							//baseType->free();
							//init device name/sourcegroup
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							strcpy(tagNode.sourcegroup,(char*)(baseType->pv));
							strcpy(tagNode.sourceserver,(char*)(baseType->pv));
							//baseType->free();

							int addTmpRes=Agpt_AddNewTag(((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->getACIServerName(),&tagNode);
							char res[6];
							res[0]=COMM_ADD_TAG;
							intToByte4J(1,(byte *)&(res[1]));
							res[5]=addTmpRes==0?RES_OK:RES_FAIL_COMMON;
							if(res[5]==0){
								int sizeTmp=((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->deviceLists.GetSize();
								int tmpI=0;
								for(tmpI=0;tmpI<sizeTmp;tmpI++){
									if(((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->deviceLists.Compare(tmpI,tagNode.sourceserver)){
										break;
									}
								}
								if(tmpI==sizeTmp){
									((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->deviceLists.Insert(tagNode.sourceserver);
									while(DRTDB_RegisterDevice(((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->m_sServerIp.GetBuffer(0),((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->m_uServerPort,tagNode.sourceserver)!=0){
										string warnMsg="Device: ";
										warnMsg.append(tagNode.sourceserver);
										warnMsg.append(" connect Error");
										LOG4CXX_WARN(logger, warnMsg);
										Sleep(10);
									};
									string tmp_str="device connect:";
									tmp_str.append(tagNode.sourceserver);
									((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->SendAndStoreMessage(tmp_str.c_str());
								}
							}
							recvSocket->PutData(res,6);
							memset(&tagNode,0,sizeof(TAG_NODE));
						}
						break;
					case COMM_ADD_VALUE:
						{

							LOG4CXX_DEBUG(logger, "Enter COMM_ADD_VALUE");
							int st=iParsePos;
							st+=COMM_HEAD_SIZE;
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							strcpy(tagvalue.szTagSource,(char*)(baseType->pv));

							LOG4CXX_DEBUG(logger, tagvalue.szTagSource);

							//baseType->free();
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							deviceName=(char*)(baseType->pv);

							LOG4CXX_DEBUG(logger, deviceName);

#ifdef  LOGOPEN
	std::ostringstream ss;
	ss << tagvalue.fValue;
	LOG4CXX_DEBUG(logger, ss.str());
#endif
							
							
							char tmpType=baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							getTagValueFromBaseType(tagvalue, *baseType,tmpType);

							result = DRTDB_MD_SendNewValue(deviceName,tagvalue, true);

							char res[60];
							res[0]=COMM_ADD_VALUE;
							intToByte4J(1,(byte *)&(res[1]));
							res[5]=result==0?RES_OK:RES_FAIL_COMMON;
							//Sleep(10);
							recvSocket->PutData(res,6);
							//this->SendData(0);
						}
						break;
					case COMM_GET_VALUE:
						{
							LOG4CXX_DEBUG(logger, "Enter COMM_GET_VALUE");
							bgve->init();
							int st=iParsePos+COMM_HEAD_SIZE;
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							int stTime=baseType->val.lv;
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							int edTime=baseType->val.lv;
							baseType->parseBaseToken(&st,iParsePos+PHLength,m_pParseBuffer);
							char* strs[3];
							strs[2]=(char *)(baseType->pv);
							strs[1]=".";
							CT2A ascii_tmp(((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->getACIServerName());
							strs[0]=ascii_tmp.m_psz;
							char* tmpTagName=myStrCat(strs,3);
							int nRs=Agda_QueryTagHistory((LPCTSTR)tmpTagName,stTime,edTime);
							//free(tmpTagName);
							//long n = Agpt_GetTagInfo((char *)(baseType->pv), &ti);
							
							if(nRs > 0) //如果查询成功，有点信息则
							{
								while(Agda_GetNextTagValue(nRs,&tv)) //取得结果集的一点信息
								{  
									bgve->praseTagval(tv);
								}
							}
							
							char *outPut=(char *)calloc(bgve->totleSize+6+(nRs>0?bgve->totleSize!=0?6:0:0),sizeof(char));
							outPut[0]=COMM_GET_VALUE;
							intToByte4J(bgve->totleSize+1+(bgve->totleSize!=0?6:0),(byte *)&(outPut[1]));
							outPut[5]=nRs>0?bgve->totleSize!=0?RES_OK:RES_FAIL_RETURN_EMPTY:(nRs==-5?RES_FAIL_NO_TAG:RES_FAIL_COMMON);
							if(outPut[5]==RES_OK){
								outPut[6]='A';
								intToByte4J(bgve->totleSize,(byte *)outPut+7);
								outPut[11]=bgve->type;
								bgve->pushData(outPut+12);
							}

							MyPutData((byte *)outPut,bgve->totleSize+6+(outPut[5]==RES_OK?6:0));
							
							free(outPut);
						}
						break;
					case COMM_GET_ALL_TAG:
						{
							LOG4CXX_DEBUG(logger, "Enter COMM_GET_ALL_TAG");
							bgve->init();
							int nRs=Agpt_QueryTagsbyNameMask(((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->getACIServerName(),"*");
							
							if(nRs > 0) //如果查询成功，有点信息则
							{
								long nTagID = 0;
								_TCHAR szTagName[C_TAGNAME_LEN];
								char *fullName=(char *)calloc(C_TAGNAME_LEN*2,sizeof(char));
								while(Agpt_EnumTagName(nRs, &nTagID, szTagName)) //获取点结果集中的一个点信息//
								{
									TAG_INFO ti;
									strcpy(fullName,((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->getACIServerName());
									strcat(fullName,".");
									strcat(fullName,szTagName);
									long n = Agpt_GetTagInfo(fullName, &ti);
									if(n == 0)
									{
										bgve->praseTaginfo(szTagName,ti.TagType);
									}
								}
								free(fullName);
							}
							
							char *outPut=(char *)calloc(bgve->totleSize+6+(nRs>0?bgve->totleSize!=0?5:0:0),sizeof(char));
							outPut[0]=COMM_GET_ALL_TAG;
							intToByte4J(bgve->totleSize+1+(bgve->totleSize!=0?5:0),(byte *)&(outPut[1]));
							outPut[5]=nRs>0?bgve->totleSize!=0?RES_OK:RES_FAIL_RETURN_EMPTY:(nRs==-5?RES_FAIL_NO_TAG:RES_FAIL_COMMON);
							if(outPut[5]==RES_OK){
								outPut[6]='A';
								intToByte4J(bgve->totleSize,(byte *)outPut+7);
								bgve->pushDataGetTag(outPut+11);
							}
							MyPutData((byte *)outPut,bgve->totleSize+6+(nRs>0?bgve->totleSize!=0?5:0:0));
							
							free(outPut);
						}
						break;
					case COMM_PING:
						{
							((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->pingCount=((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->pingCount+1;
						}
						break;
					default:
						break;
				}
				BOOL bErrorPack = FALSE;
				if (result != 0) {
					bErrorPack = TRUE;
					char tmp_s[16];
					CString ret_str, tagid_str;
					_ltoa_s(result, tmp_s, 10);
					ret_str = tmp_s;
					_ltoa_s(tagvalue.lTagID, tmp_s, 10);
					tagid_str = tmp_s;

					CString tmp_str = "Error Frame, Return code : " + ret_str + ", TagID : " + tagid_str;
					((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->SendAndStoreMessage(tmp_str);
				}
				((CKernelMonitorv1Dlg*)(recvSocket->m_pDlgPointer))->AddPack(PHLength, bErrorPack);	// m_lPackCount m_lDataSize
				iParsePos += PHLength;
			}
		}
	}while (!bExit);
	baseType->~BaseType();
	//DRTDB_Flush();
	if (m_lPos >= iParsePos)
	{
		memcpy(m_pParseBuffer, m_pParseBuffer + iParsePos, m_lPos - iParsePos);
		m_lPos = m_lPos - iParsePos;
	}
	return;
}



int DataExecutor::Run(){
	BOOL bExit = FALSE;
	while (!bExit) {
		if (ParesData(10) == 0) {
			if (IsStopping(0)) {
				bExit = TRUE;
			}
		}
	}
	Stop();
	return ExitInstance();
}

int DataExecutor::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CBaseThread::ExitInstance();
}



BEGIN_MESSAGE_MAP(DataExecutor, CBaseThread)

END_MESSAGE_MAP()

void DataExecutor::SetSocket(CMonitorReceiveSocket * socket)
{
	recvSocket = socket;
}


DataExecutor::~DataExecutor()
{
}
