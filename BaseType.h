#pragma once
class BaseType
{
public:
	BaseType(void);
	~BaseType(void);
	//void free();
	char parseBaseToken(int *st,int ed,char *data);

	union{
		int lv;
		float fv;
		unsigned short sv;
		unsigned char tmp[0];
		bool bv;
		char cv;
	}val;
	void *pv;
	char type;
	bool isReleased;
	

};

