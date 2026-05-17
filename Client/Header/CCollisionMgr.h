#pragma once

#include "CObjMgr_YJ.h"
class CCollisionMgr
{
	DECLARE_SINGLE(CCollisionMgr)

public:
	void CheckCollision_SAT(YJUTIL::OBJ_TYPE TYPE1, YJUTIL::OBJ_TYPE TYPE2);
	//bool IsCollide_SAT(const CObj* Obj1, const CObj* Obj2, D3DXVECTOR3* vAxis, float* fMinOverlapped); //MFV 넣어보기
	bool IsCollide_SAT(const CObjYJ* Obj1, const CObjYJ* Obj2, D3DXVECTOR3* pOutAxis,
		float* pOutOverlap);
	void Project(const CObjYJ* obj, const D3DXVECTOR3 vAxis, float& fOutMin, float& fOutMax);

	void ResolveCollision(CObjYJ* Src,
		CObjYJ* Dst,
		const D3DXVECTOR3& axis,
		float overlap)
	{
		D3DXVECTOR3 fixedAxis = axis;

		D3DXVECTOR3 dir =
			Src->GetPos() - Dst->GetPos();

		// axis 방향 맞추기 ⭐⭐⭐
		if (D3DXVec3Dot(&dir, &fixedAxis) < 0)
			fixedAxis *= -1.f;
		D3DXVec3Normalize(&fixedAxis, &fixedAxis);

		D3DXVECTOR3 push = fixedAxis * overlap;

		// 플레이어만 밀기
		if (Src->GetType() == OBJ_PLAYER)
			Src->AddPos(push);

		else if (Dst->GetType() == OBJ_PLAYER)
			Dst->AddPos(-push);

	}
};

