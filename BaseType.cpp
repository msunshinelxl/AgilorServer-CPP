#include "stdafx.h"
#include "BaseType.h"


BaseType::BaseType(void)
{
}


BaseType::~BaseType(void)
{
	memset(this,0,sizeof(BaseType));
}

//void BaseType::free(){
//	if(isReleased==false){
//		std::free(pv);
//		isReleased=true;
//	}
//}

char BaseType::parseBaseToken(int *st,int ed,char *data){
	char tmpType=data[*st];
	char res=0;
	(*st)+=1;
	switch(tmpType){
	case COMM_BOOL:
		type=COMM_BOOL;
	case COMM_INT8:
		if(tmpType==COMM_INT8)
			type=COMM_INT8;
		val.cv=data[*st];
		res='B';
		(*st)+=1;
		break;
	case COMM_INT16:
		type=COMM_INT16;
		val.sv=((data[(*st)+1] << 8) | (data[*st]));
		(*st)+=2;
		break;
	case COMM_INT64:
		type=COMM_INT64;
	case COMM_INT32:
		if(tmpType==COMM_INT32)
			type=COMM_INT32;
		res='L';
	case COMM_FLOAT:
		if(tmpType==COMM_FLOAT){
			res='R';
			type=COMM_FLOAT;
		}
		for(int i=0;i<4;i++)
			val.tmp[i]=data[(*st)+i];
		(*st)+=4;
		break;
	case COMM_STRING:
		type=COMM_STRING;
		res='S';
		int length=((data[(*st)+3] << 24) |(data[(*st)+2] << 16) |(data[(*st)+1] << 8) | (data[*st]));
		(*st)+=4;
		isReleased=false;
		pv=data+(*st);
		(*st)+=length;
		break;
	}
	return res;
}