#include "pch.h"
#include "CObjMgr_YJ.h"
#include "CCollisionMgr.h"

using namespace YJUTIL;

CObjMgr_YJ* CObjMgr_YJ::m_pInstance = nullptr;

CObjMgr_YJ::CObjMgr_YJ()
{

}

CObjMgr_YJ::~CObjMgr_YJ()
{

}

void CObjMgr_YJ::Initialize()
{
}
void CObjMgr_YJ::Update()
{
	int iResult;

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_vecObjList[i].begin(); iter != m_vecObjList[i].end();) {

			iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD) {
				Safe_Delete(*iter);
				iter = m_vecObjList[i].erase(iter);
			}
			else {
				++iter;
			}
		}

	}

}

void CObjMgr_YJ::LateUpdate()
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_vecObjList[i])
		{
			if (pObj)
				pObj->LateUpdate();

		}
	}
	GET_SINGLE(CCollisionMgr)->CheckCollision_SAT(OBJ_PLAYER, OBJ_OBSTACLE);
	//GET_SINGLE(CCollisionMgr)->CheckCollision_SAT(OBJ_OBSTACLE, OBJ_PLAYER);
}

void CObjMgr_YJ::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_vecObjList[i])
		{
			if (pObj)
				pObj->Render(hDC);
		}
	}
}


void CObjMgr_YJ::Load_ObjData(const TCHAR* szPath, vector<DATA>* pObstacleList)
{
	//Release();

	if (pObstacleList)
	{
		pObstacleList->clear();
	}

	HANDLE hObjFile = CreateFile(szPath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hObjFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Load File", _T("Fail"), MB_OK);
		return;
	}

	else if (hObjFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwByte(0);


		int iObjCount = 0;
		ReadFile(hObjFile, &iObjCount, sizeof(int), &dwByte, NULL);

		while (true)
		{

			if (0 == dwByte) break;


			DATA tData{};

			ReadFile(hObjFile, tData.szName, sizeof(TCHAR) * 32, &dwByte, NULL);
			// 2. 센터
			ReadFile(hObjFile, &tData.vCenter,
				sizeof(D3DXVECTOR3), &dwByte, NULL);

			// 3. 라인 개수
			int iLineCount = 0;
			ReadFile(hObjFile, &iLineCount,
				sizeof(int), &dwByte, NULL);

			// 4. 라인 데이터
			for (int j = 0; j < iLineCount; ++j)
			{
				LINE_DATA line{};
				ReadFile(hObjFile, &line,
					sizeof(LINE_DATA), &dwByte, NULL);

				tData.vecLineData.push_back(line);
			}

			// 5. 타입 분류
			if (wcscmp(tData.szName, L"OBSTACLE") == 0)
			{
				pObstacleList->push_back(tData);
			}
		}
		CloseHandle(hObjFile);
		MessageBox(g_hWnd, L"Load File", _T("성공"), MB_OK);
	}
}

void CObjMgr_YJ::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_vecObjList[i].begin(), m_vecObjList[i].end(), tagDelete());
		m_vecObjList[i].clear();
	}
}