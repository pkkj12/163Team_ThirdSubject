#pragma once
#include "Define_JW.h"
#include <queue>

#define STOCK_OBSTACLE_COUNT 1000

class CObj_JW;

// 옵스타클 풀링/스폰 해주는 매니저? 여러 기능이 있어서 썩 좋지는 않은 구조일거임
class CObstacleMgr_JW
{
	DECLARE_SINGLETON(CObstacleMgr_JW)

private:
	CObstacleMgr_JW();
	~CObstacleMgr_JW();

private:
	void MakeStockObstacle();

public:
	void Update(); // 시간 재다가 시간이 지나면 장애물->오브젝트로 넘겨야 함
	void PushObstacle(CObj_JW* pObstacle);

private:
	void MakeObstacle();

private:
	queue<CObj_JW*> m_queueObstacle;
	_ulong m_dwCurSpawnTime;
	_ulong m_dwSpawnCoolTime;
};

