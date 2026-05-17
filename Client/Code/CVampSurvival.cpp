#include "pch.h"
#include "CVampSurvival.h"
#include "CPlayer_YJ.h"
#include "CTimeMgr_YJ.h"
#include "CObjMgr_YJ.h"
#include "CObstacle.h"
#include "CLine_YJ.h"
#include "CScrollMgr_YJ.h"

CVampSurvival::CVampSurvival() : m_pPlayer(nullptr)
{
}

CVampSurvival::~CVampSurvival()
{
}

void CVampSurvival::Initialize()
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer_YJ;
		m_pPlayer->Ready();
		m_pPlayer->SetType(OBJ_PLAYER);
	}
	GET_SINGLE(CObjMgr_YJ)->AddObject(OBJ_PLAYER, m_pPlayer);
	GET_SINGLE(CTimeMgr_YJ)->Initialize();


	//GET_SINGLE(CScrollMgr_YJ)->Scroll_Lock(1920.f, 1150.f);
	// 라인 오브젝트 생성
	GET_SINGLE(CObjMgr_YJ)->Load_ObjData(L"../Data/ObjectLine.dat",&m_tObstacles);
	for (auto obstacle : m_tObstacles)
	{
		if (!lstrcmp(obstacle.szName, L"OBSTACLE"))
		{
			CObstacle* pObstacle = new CObstacle;
			//if (FAILED(pObstacle->Ready())) return;


			pObstacle->SetPos(obstacle.vCenter);

			for (auto& line : obstacle.vecLineData)
			{
				CLine_YJ* pLine = new CLine_YJ(line.tBegin, line.tEnd);
				pObstacle->AddLine(pLine);
				// ⭐ 월드 → 로컬 변환
				D3DXVECTOR3 vLocalStart = line.tBegin - obstacle.vCenter;
				D3DXVECTOR3 vLocalEnd = line.tEnd - obstacle.vCenter;

				pObstacle->AddOriginVertex(vLocalStart);
				pObstacle->AddOriginVertex(vLocalEnd);
			}
			pObstacle->SetType(OBJ_OBSTACLE);
			GET_SINGLE(CObjMgr_YJ)->AddObject(OBJ_OBSTACLE, pObstacle);
		}
	}
}

void CVampSurvival::Update()
{

	GET_SINGLE(CTimeMgr_YJ)->Update();
	GET_SINGLE(CObjMgr_YJ)->Update();
	
}

void CVampSurvival::LateUpdate()
{
	GET_SINGLE(CObjMgr_YJ)->LateUpdate();
	//GET_SINGLE(CScrollMgr_YJ)->Scroll_Lock(1920.f, 600.f);
}

void CVampSurvival::Render(HDC hMemDC)
{
	GET_SINGLE(CObjMgr_YJ)->Render(hMemDC);
}

void CVampSurvival::Release()
{
}
