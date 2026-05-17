#pragma once
#include "CBase.h"
#include "Define_JW.h"

class CObj_JW;

class CObjMgr_JW
{
	DECLARE_SINGLETON(CObjMgr_JW)

private:
	explicit CObjMgr_JW();
	virtual ~CObjMgr_JW();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	CObj_JW* GetFrontObj(ObjType_JW eType) { return m_pObjListArr[(_ushort)eType].front(); }
	list<CObj_JW*> GetObjList(ObjType_JW eType) 
	{
		return m_pObjListArr[(_ushort)eType];
	}
	void PushBackObj(ObjType_JW eType, CObj_JW* pObj);
	void DeleteList(ObjType_JW eType);

private:
	list<CObj_JW*> m_pObjListArr[(_ushort)ObjType_JW::End];
};

