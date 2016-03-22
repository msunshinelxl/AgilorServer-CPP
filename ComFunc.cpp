#include "stdafx.h"
#include "ComFunc.h"


ComFunc::ComFunc(void)
{
}


ComFunc::~ComFunc(void)
{
}

void ComFunc::initTagVal(TAG_NODE& data){
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