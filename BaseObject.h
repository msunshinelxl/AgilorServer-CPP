// BaseObject.h: interface for the CBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEOBJECT_H__D0AF6D74_0192_4C91_8FA6_2125732BAF25__INCLUDED_)
#define AFX_BASEOBJECT_H__D0AF6D74_0192_4C91_8FA6_2125732BAF25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBaseObject  
{
public:
	CBaseObject();
	virtual ~CBaseObject();
	void	Lock();
	void	Unlock();

protected:
	CRITICAL_SECTION m_CriticalSection;

};

#endif // !defined(AFX_BASEOBJECT_H__D0AF6D74_0192_4C91_8FA6_2125732BAF25__INCLUDED_)
