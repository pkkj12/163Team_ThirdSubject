#include "pch.h"
#include "CObstacleMgr_JW.h"

#include "CObj_JW.h"
#include "CObjMgr_JW.h"
#include "CObstacle_JW.h"

IMPLEMENT_SINGLETON(CObstacleMgr_JW)

CObstacleMgr_JW::CObstacleMgr_JW()
	: m_dwCurSpawnTime(GetTickCount()), m_dwSpawnCoolTime(460)
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

		int iRand = rand() % 4;

		if (iRand == 0)
		{

		}
		else if (iRand == 1)
		{
			MakeObstacle();
			MakeObstacle();
		}
		else if (iRand == 2)
		{
			MakeObstacle();
			MakeObstacle();
			MakeObstacle();
		}
		else if (iRand = rand() % 2)
		{
			MakeObstacle();
			MakeObstacle();
			MakeObstacle();
			MakeObstacle();
			MakeObstacle();
		}
	}

	// if (!CObjMgr_JW::GetInstance()->GetObjList(ObjType_JW::Obstacle).empty())
	//	DEBUG_JW::DBG_WindowText(CObjMgr_JW::GetInstance()->GetFrontObj(ObjType_JW::Obstacle)->GetDistance());
}

void CObstacleMgr_JW::PushObstacle(CObj_JW* pObstacle)
{
//	pObstacle->Initialize();
//	m_queueObstacle.push(pObstacle);
}

void CObstacleMgr_JW::MakeObstacle()
{
	if (m_queueObstacle.size() == 0)
		MakeStockObstacle();

	m_queueObstacle.front()->Initialize();

	//CObj_JW* pObstacle = new CObstacle_JW;
	//pObstacle->SetParent_JW(CObjMgr_JW::GetInstance()->GetFrontObj(ObjType_JW::Hexagon));
	//pObstacle->Initialize();

	CObjMgr_JW::GetInstance()->PushBackObj
	(
		ObjType_JW::Obstacle,
		m_queueObstacle.front()
	);

	m_queueObstacle.pop();
}
