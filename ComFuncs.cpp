#include "stdafx.h"

vector<string> strSplit(string source,CString splitItem)
{
	int start=0;
	int pos=source.find(splitItem,start);
	vector<string> res;

	while(true){
		if(pos<0){
			res.push_back(source.substr(start));
			break;
		}else{
			res.push_back((source.substr(start,pos-start)));
			start = pos+splitItem.GetLength();
			pos =source.find(splitItem,start);
		}
	}
	return res;
}

bool inStringArray(vector<string> stringArray,string item){
	for (vector<string>::const_iterator iter = stringArray.cbegin(); iter != stringArray.cend(); iter++)
    {
		if(item.compare((*iter))==0){
			return true;
		}
    }
	return false;
}

void initTagVal(TAG_NODE& data){
	data.scan=1;
	data.pointtype = 'R';
	data.rval = 1024.1024;
	data.sourceserver[0] = 0;
	data.sourcegroup[0] = 0;
	
	data.name[0] = 0;
	data.sourcetag[0] = 0;
	data.descriptor[0] = 0;
	data.engunits[0] = 0;
	data.istat = 1638;
	data.typicalvalue = 0;
	data.excmin = 0;
	data.excmax = 0;
	data.excdev = 0;
	data.upperlimit = 0;
	data.lowerlimit = 0;
	data.alarmhihi = 0;
	data.alarmlolo = 0;
	data.alarmtype = 0;
	data.alarmmin = 0;
	data.alarmmax = 0;
	data.lasttime = 0;
	data.archiving=1;
}

void getTagValueFromBaseType(TAG_VALUE_LOCAL &dist,BaseType src,char type){
	dist.cTagType=type;
	switch(type){
	case 'R':
		dist.fValue=src.val.fv;
		break;
	case 'L':
		dist.lValue=src.val.lv;
		break;
	case 'B':
		dist.bValue=src.val.bv;
		break;
	case 'S':
		strcpy(dist.szValue,(char *)(src.pv));
		break;
	}
}

void  intToByte4J(int i,byte *bytes,int size)
{
     //byte[] bytes = new byte[4];
    memset(bytes,0,sizeof(byte) *  size);
    bytes[0] = (byte) (0xff & i);
    bytes[1] = (byte) ((0xff00 & i) >> 8);
    bytes[2] = (byte) ((0xff0000 & i) >> 16);
    bytes[3] = (byte) ((0xff000000 & i) >> 24);
    return ;
 }

long time2Long(char *time){
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
	memcpy(year,time,4);
	year[4]=0;
	time+=4;
	memcpy(month,time,2);
	month[2]=0;
	time+=2;
	memcpy(day,time,2);
	day[2]=0;
	time+=2;
	memcpy(hour,time,2);
	hour[2]=0;
	time+=2;
	memcpy(minute,time,2);
	minute[2]=0;
	time+=2;
	memcpy(second,time,2);
	minute[2]=0;
	int yearInt=atoi(year);
	int monthInt=atoi(month);
	int dayInt=atoi(day);
	int hourInt=atoi(hour);
	int minuteInt=atoi(minute);
	int secondInt=atoi(second);
	return Agtm_DateTime2Long(hourInt,minuteInt,secondInt,yearInt,monthInt,dayInt);
}

char *myStrCat(char ** strs,int num){
	if(num==0){
		return NULL;
	}
	int length=0;
	for(int i=0;i<num;i++){
		length+=strlen(strs[i]);
	}
	char* res=(char *)calloc(length,sizeof(char));
	if(num>0){
		memcpy(res,strs[0],strlen(strs[0]));
	}
	for(int i=1;i<num;i++){
		strcat(res,strs[i]);
	}
	return res;
}

//void parseBaseToken(BaseType* res,int *st,int ed,char *data){
//	char tmpType=data[*st];
//	(*st)+=1;
//	switch(tmpType){
//	case COMM_BOOL:
//		res->type=COMM_BOOL;
//	case COMM_INT8:
//		if(tmpType==COMM_INT8)
//			res->type=COMM_INT8;
//		res->val.cv=data[*st];
//		(*st)+=1;
//		break;
//	case COMM_INT16:
//		res->type=COMM_INT16;
//		res->val.sv=((data[(*st)+1] << 8) | (data[*st]));
//		(*st)+=2;
//		break;
//	case COMM_INT64:
//		res->type=COMM_INT64;
//	case COMM_INT32:
//		if(tmpType==COMM_INT32)
//			res->type=COMM_INT32;
//	case COMM_FLOAT:
//		if(tmpType==COMM_FLOAT)
//			res->type=COMM_FLOAT;
//		for(int i=0;i<4;i++)
//			res->val.tmp[i]=data[(*st)+i];
//		(*st)+=4;
//		break;
//	case COMM_STRING:
//		res->type=COMM_STRING;
//		int length=((data[(*st)+3] << 24) |(data[(*st)+2] << 16) |(data[(*st)+1] << 8) | (data[*st]));
//		(*st)+=4;
//		res->isReleased=false;
//		res->val.pv=calloc(sizeof(char),length+1);
//		memcpy(res->val.pv,data+(*st),length);
//		(*st)+=length;
//		break;
//	}
//}


int byte2Int(char *data){
	return ((data[3] << 24) |(data[+2] << 16) |(data[+1] << 8) | (data[0]));
}
//void praseAddTagPackage(BaseType* baseType,int st,int iParsePos,int pHeadLength,char *m_pBuffer,TAG_NODE& tagNode){
//
//	parseBaseToken(baseType,&st,iParsePos+pHeadLength,m_pBuffer);
//	strcpy(tagNode.sourcetag,(char*)(baseType->val.pv));
//	strcpy(tagNode.name,(char*)(baseType->val.pv));
//	free(baseType->val.pv);
//	//init device name/sourcegroup
//	parseBaseToken(baseType,&st,iParsePos+pHeadLength,m_pBuffer);
//	strcpy(tagNode.sourcegroup,(char*)(baseType->val.pv));
//	strcpy(tagNode.sourceserver,(char*)(baseType->val.pv));
//	free(baseType->val.pv);
//	int addTmpRes=Agpt_AddNewTag(((CKernelMonitorv1Dlg*)m_pDlgPointer)->getACIServerName(),&tagNode);
//	char res[2];
//	res[0]=COMM_ADD_TAG;
//	res[1]=addTmpRes==0?0:-1;
//
//}