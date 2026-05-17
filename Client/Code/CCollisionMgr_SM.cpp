#include "pch.h"
#include "CCollisionMgr_SM.h"

CCollisionMgr_SM* CCollisionMgr_SM::m_pInstance_SM = nullptr;

CCollisionMgr_SM::CCollisionMgr_SM()
{
}

CCollisionMgr_SM::~CCollisionMgr_SM()
{
}



void CCollisionMgr_SM::Collision_AABB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex)
{
	bool bIsCollide = Check_AABB_SM(vecDstVertex, vecSrcVertex);

	if (bIsCollide)
	{

	}
}

void CCollisionMgr_SM::Collision_OBB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex)
{

}

bool CCollisionMgr_SM::Check_AABB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex)
{
	POINT tDstLow{}, tDstHigh{};
	POINT tSrcLow{}, tSrcHigh{};

	for (auto&& iter = vecDstVertex.begin(); iter != vecDstVertex.end(); ++iter)
	{
		//Dst_X//
		if (tDstLow.x > (*iter).x || tDstHigh.x < (*iter).x)
		{
			if ((*iter).x < tDstLow.x)
			{
				tDstLow.x = (*iter).x;
			}

			else if ((*iter).x > tDstHigh.x)
			{
				tDstHigh.x = (*iter).x;
			}
		}

		//Dst_Y//
		if (tDstLow.y > (*iter).y || tDstHigh.y < (*iter).y)
		{
			if ((*iter).y < tDstLow.y)
			{
				tDstLow.y = (*iter).y;
			}

			else if ((*iter).y > tDstHigh.y)
			{
				tDstHigh.y = (*iter).y;
			}
		}

	}

	for (auto&& iter = vecSrcVertex.begin(); iter != vecSrcVertex.end(); ++iter)
	{
		//Src_X//
		if (tSrcLow.x > (*iter).x || tSrcHigh.x < (*iter).x)
		{
			if ((*iter).x < tSrcLow.x)
			{
				tSrcLow.x = (*iter).x;
			}

			else if ((*iter).x > tSrcHigh.x)
			{
				tSrcHigh.x = (*iter).x;
			}
		}

		//Src_Y//
		if (tSrcLow.y > (*iter).y || tSrcHigh.y < (*iter).y)
		{
			if ((*iter).y < tSrcLow.y)
			{
				tSrcLow.y = (*iter).y;
			}

			else if ((*iter).y > tSrcHigh.y)
			{
				tSrcHigh.y = (*iter).y;
			}
		}

	}

	POINT tDstHalfLength = { labs((tDstHigh.x - tDstLow.x) >> 1), labs((tDstHigh.y - tDstLow.y) >> 1) };
	POINT tSrcHalfLength = { labs((tSrcHigh.x - tSrcLow.x) >> 1), labs((tSrcHigh.y - tSrcLow.y) >> 1) };

	POINT tDstMidPoint = { (tDstHigh.x - tDstHalfLength.x), (tDstHigh.y - tDstHalfLength.y) };
	POINT tSrcMidPoint = { (tSrcHigh.x - tSrcHalfLength.x), (tSrcHigh.y - tSrcHalfLength.y) };

	POINT fMidPointLength = { labs(tDstMidPoint.x - tSrcMidPoint.x), labs(tDstMidPoint.y - tSrcMidPoint.y) };

	if (tDstHalfLength.x + tSrcHalfLength.x > fMidPointLength.x && tDstHalfLength.y + tSrcHalfLength.y > fMidPointLength.y)
	{
		return TRUE;
	}


	return FALSE;
}

bool CCollisionMgr_SM::Check_OBB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex)
{
	return FALSE;
}
