#include "pch.h"
#include "CObjMgr_JW.h"
#include "CObstacleMgr_JW.h"
#include "CObj_JW.h"

IMPLEMENT_SINGLETON(CObjMgr_JW)

CObjMgr_JW::CObjMgr_JW()
{

}

CObjMgr_JW::~CObjMgr_JW()
{
	Release();
}

void CObjMgr_JW::Initialize() 
{

}

int CObjMgr_JW::Update()
{
	for (int i = 0; i < (_ushort)ObjType_JW::End; ++i)
	{
		for (auto iter = m_pObjListArr[i].begin(); iter != m_pObjListArr[i].end();)
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DESTROY_JW)
			{
				//if (Safe_Release<CObj_JW*>(*iter) == 0);
					
				Safe_Delete<CObj_JW*>((*iter));
				iter = m_pObjListArr[i].erase(iter);
			}
			else if (iResult == OBJ_HANDOVER_JW)
			{
				Safe_Delete<CObj_JW*>((*iter));
				iter = m_pObjListArr[i].erase(iter);

			//	CObstacleMgr_JW::GetInstance()->PushObstacle((*iter));
			//	iter = m_pObjListArr[i].erase(iter);
			}

			if (iter == m_pObjListArr[i].end())
				break;
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr_JW::LateUpdate() 
{
	for (int i = 0; i < (_ushort)ObjType_JW::End; ++i)
	{
		for_each(m_pObjListArr[i].begin(), m_pObjListArr[i].end(), [](CObj_JW*& pObj) 
			{
				pObj->LateUpdate();
			});
	}
}

void CObjMgr_JW::Render(HDC hDC)
{
	for (int i = 0; i < (_ushort)ObjType_JW::End; ++i)
	{
		for_each(m_pObjListArr[i].begin(), m_pObjListArr[i].end(), [&hDC](CObj_JW*& pObj)
			{
				pObj->Render(hDC);
			});
	}
}

void CObjMgr_JW::PushBackObj(ObjType_JW eType, CObj_JW* pObj)
{
	m_pObjListArr[(_ushort)eType].push_back(pObj);
}

void CObjMgr_JW::DeleteList(ObjType_JW eType)
{
	_ushort i = (_ushort)eType;

	for (auto iter = m_pObjListArr[i].begin(); iter != m_pObjListArr[i].end();)
	{
		Safe_Delete<CObj_JW*>(*iter);
		iter = m_pObjListArr[i].erase(iter);

		if (iter == m_pObjListArr[i].end())
			break;
		else
			++iter;
	}
}

void CObjMgr_JW::Release()
{
	for (int i = 0; i < (_ushort)ObjType_JW::End; ++i)
	{
		for (auto iter = m_pObjListArr[i].begin(); iter != m_pObjListArr[i].end();)
		{
			Safe_Delete<CObj_JW*>(*iter);
			iter = m_pObjListArr[i].erase(iter);
			
			if (iter == m_pObjListArr[i].end())
				break;
			else
				++iter;
		}
	}
}
