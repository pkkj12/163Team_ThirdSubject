#pragma once

#include "CObjYJ.h"
class CObjMgr_YJ
{

	DECLARE_SINGLE(CObjMgr_YJ)

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	template<typename T>
	T* CreateObject(OBJ_TYPE eID)
	{
		if (eID >= OBJ_END)
			return nullptr;

		static_assert(std::is_convertible_v<T*, CObjYJ*>);	// 타입 검증 stl

		T* pObj = new T();
		pObj->Initialize();
		pObj->SetType(eID);

		m_vecObjList[eID].push_back(pObj);

		return pObj;
	}

	void	AddObject(OBJ_TYPE eType, CObjYJ* pObj)
	{
		if (eType >= OBJ_END || !pObj) return;

		m_vecObjList[eType].push_back(pObj);
	}

public:
	vector<CObjYJ*>& GetObjList(YJUTIL::OBJ_TYPE eType)
	{
		if (eType == OBJ_MBULLET && !m_vecObjList[eType].empty())
		{
			wcout << format(L"{}",m_vecObjList[eType].empty()) << endl;
		}
		return m_vecObjList[eType];
	}
	CObjYJ* GetPlayer() const { return m_vecObjList[OBJ_PLAYER].front(); }

	void Load_ObjData(const TCHAR* szPath, vector<DATA>* pObstacleList);
private:
	vector<CObjYJ*> m_vecObjList[YJUTIL::OBJ_END];
};

