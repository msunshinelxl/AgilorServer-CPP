#pragma once
class BaseGetValueEntity
{
public:
	BaseGetValueEntity(void);
	~BaseGetValueEntity(void);
	vector<int> intArray;
	vector<char*>strArray;
	vector<float>floatArray;
	vector<bool>boolArray;
	vector<int>timeArray;

	vector<char> typeArray;
	
	int totleSize;
	void BaseGetValueEntity::praseTagval(TAGVAL);
	void BaseGetValueEntity::pushData(char *dist);
	void BaseGetValueEntity::init();
	void BaseGetValueEntity::praseTaginfo(char * tagName,char type);
	void BaseGetValueEntity::pushDataGetTag(char*dist);
	bool strArrayIsUsed;
	char type;
};

