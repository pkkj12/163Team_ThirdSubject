#include "pch.h"
#include "CCollisionMgr_JW.h"
#include "CObj_JW.h"
#include "CObjMgr_JW.h"

void CCollisionMgr_JW::CheckCollision_SAT(ObjType_JW eType1, ObjType_JW eType2)
{
	const auto ObjList1 = CObjMgr_JW::GetInstance()->GetObjList(eType1);
	const auto ObjList2 = CObjMgr_JW::GetInstance()->GetObjList(eType2);

	for (auto& Src : ObjList1)
	{
		for (auto& Dst : ObjList2) 
		{
			if (IsCollide_SAT(Src, Dst))
			{
				Src->OnCollisionStay(true);
			}
			else
			{
//				Src->OnCollisionStay(false);
			}
		}
	}
}

bool CCollisionMgr_JW::IsCollide_SAT(const CObj_JW* Obj1, const CObj_JW* Obj2)
{
	const auto& vecVertexs1 = Obj1->GetWorldVertex();
	const auto& vecVertexs2 = Obj2->GetWorldVertex();

	vector<D3DXVECTOR3> edges;
	edges.reserve(vecVertexs1.size() + vecVertexs2.size());

	//CObj1의 모서리
	for (size_t i = 0; i < vecVertexs1.size(); ++i) 
	{
		edges.push_back(*vecVertexs1[i] - *vecVertexs1[(i + 1) % vecVertexs1.size()]);
	}

	//CObj2의 모서리
	for (size_t i = 0; i < vecVertexs2.size(); ++i) {

		edges.push_back(*vecVertexs2[i] - *vecVertexs2[(i + 1) % vecVertexs2.size()]);
	}

	// 모서리 => 법선 벡터 ( 축 ) 
	for (const auto& e : edges) 
	{

		D3DXVECTOR3 vAxis;
		vAxis = { -e.y , e.x, 0.f };
		D3DXVec3Normalize(&vAxis, &vAxis);
		float fOutMin1, fOutMax1;
		float fOutMin2, fOutMax2;
		Project(Obj1, vAxis, fOutMin1, fOutMax1);
		Project(Obj2, vAxis, fOutMin2, fOutMax2);

		if (fOutMax1 < fOutMin2 || fOutMax2 < fOutMin1)
			return false;

	}

	//MFV 추가해보기

	return true;
}

void CCollisionMgr_JW::Project(const CObj_JW* Obj, const _vec3 vAxis, float& fOutMin, float& fOutMax)
{
	const auto& vecVertexs = Obj->GetWorldVertex();
	fOutMin = fOutMax = D3DXVec3Dot(vecVertexs[0], &vAxis);

	for (int i = 1; i < vecVertexs.size(); ++i) 
	{
		float fDot = D3DXVec3Dot(vecVertexs[i], &vAxis);
		fOutMin = min(fOutMin, fDot);
		fOutMax = max(fOutMax, fDot);
	}
}

void CCollisionMgr_JW::CheckCollision()
{
	CObj_JW* pPlayer =
		CObjMgr_JW::GetInstance()->GetFrontObj(ObjType_JW::Player);

	const _uint iPlayerIDX = pPlayer->GetIDX();

	auto vecObstacles =
		CObjMgr_JW::GetInstance()->GetObjList(ObjType_JW::Obstacle);

	bool bIsCollided(false);

	for (auto& pObstacle : vecObstacles)
	{
		if (pObstacle->GetIDX() == iPlayerIDX)
		{
			if (pObstacle->GetDistance() >= 1.1f &&
				pObstacle->GetDistance() <= 1.28f)
			{
				bIsCollided = true;
				break;
			}
		}
	}

	pPlayer->OnCollisionStay(bIsCollided);
}
