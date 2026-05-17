#include "pch.h"
#include "CObstacleMgr_JW.h"

#include "CObj_JW.h"
#include "CObjMgr_JW.h"
#include "CObstacle_JW.h"

IMPLEMENT_SINGLETON(CObstacleMgr_JW)

CObstacleMgr_JW::CObstacleMgr_JW()
	: m_dwCurSpawnTime(GetTickCount()), m_dwSpawnCoolTime(400)
{
	MakeStockObstacle();
}

CObstacleMgr_JW::~CObstacleMgr_JW()
{
	while (!m_queueObstacle.empty())
	{
		Safe_Delete<CObj_JW*>(m_queueObstacle.front());
		m_queueObstacle.pop();
	}
}

void CObstacleMgr_JW::MakeStockObstacle()
{
 	for (int i = 0; i < STOCK_OBSTACLE_COUNT; ++i)
	{
		CObj_JW* pObstacle = new CObstacle_JW;
		pObstacle->SetParent_JW(CObjMgr_JW::GetInstance()->GetFrontObj(ObjType_JW::Hexagon));
		m_queueObstacle.push(pObstacle);
	}
}

void CObstacleMgr_JW::Update()
{
	if (m_dwCurSpawnTime + m_dwSpawnCoolTime < GetTickCount())
	{
		m_dwCurSpawnTime = GetTickCount();

		int iRand = rand() % 3;

		if (iRand == 0)
		{

		}
		else if (iRand == 1)
		{
			MakeObstacle();
			MakeObstacle();
		}
		else
		{
			MakeObstacle();
			MakeObstacle();
			MakeObstacle();
		}
	}
}

void CObstacleMgr_JW::PushObstacle(CObj_JW* pObstacle)
{
	pObstacle->Initialize();
	m_queueObstacle.push(pObstacle);
}

void CObstacleMgr_JW::MakeObstacle()
{
	if (m_queueObstacle.size() == 0)
		MakeStockObstacle();

	CObj_JW* pObstacle = m_queueObstacle.front();
	pObstacle->Initialize();
	
	m_queueObstacle.pop();

//	CObj_JW* pObstacle = new CObstacle_JW;
//	pObstacle->SetParent_JW(CObjMgr_JW::GetInstance()->GetFrontObj(ObjType_JW::Hexagon));
//	pObstacle->Initialize();

	CObjMgr_JW::GetInstance()->PushBackObj
	(
		ObjType_JW::Obstacle,
		pObstacle
	);
}
