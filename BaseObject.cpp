// BaseObject.cpp: implementation of the CBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseObject::CBaseObject()
{
	InitializeCriticalSection(&m_CriticalSection);
}

CBaseObject::~CBaseObject()
{
	DeleteCriticalSection(&m_CriticalSection);
}

void CBaseObject::Lock()
{
	EnterCriticalSection(&m_CriticalSection);
}

void CBaseObject::Unlock()
{
	LeaveCriticalSection(&m_CriticalSection);
}