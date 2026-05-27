#include "pch.h"
#include "CCollisionMgr.h"
#include "CBullet_YJ.h"
#include "CObjYJ.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;
CCollisionMgr::CCollisionMgr() {}
CCollisionMgr::~CCollisionMgr() {}

void CCollisionMgr::CheckCollision_SAT(YJUTIL::OBJ_TYPE  TYPE1, YJUTIL::OBJ_TYPE  TYPE2)
{

	const auto& ObjList1 = CObjMgr_YJ::GetInstance()->GetObjList(TYPE1);
	const auto& ObjList2 = CObjMgr_YJ::GetInstance()->GetObjList(TYPE2);

	if (ObjList1.empty() || ObjList2.empty()) return;

	for (auto& Src : ObjList1) {
		for (auto& Dst : ObjList2) {
			D3DXVECTOR3 axis;
			float overlap;
			//충돌 처리  ( 임시 )
			//D3DXVECTOR3 vAxis = { 0, 0, 0 };
			//float fMinOverlapped = static_cast<float>(INF);
			//if (IsCollide_SAT(Src, Dst, &vAxis, &fMinOverlapped)) {
			if (IsCollide_SAT(Src, Dst, &axis, &overlap)) {

				if((Src->GetType() == OBJ_OBSTACLE || Dst->GetType() == OBJ_OBSTACLE)
					&& Dst->GetType() != OBJ_MBULLET)
					ResolveCollision(Src, Dst, axis, overlap);
				//for (auto& v : Src->GetVecWorldVertexs()) {
				//	cout << " Src : " << v.x << " " << v.y << endl;
				//}
				//for (auto& v : Dst->GetVecWorldVertexs()) {
				//	cout << " Dst : " << v.x << " " << v.y << endl;
				//}

				Src->SetCollide(true);
				Dst->SetCollide(true);
				Src->SetCollide(Dst);
				Dst->SetCollide(Src);
			}
		}
	}
}

//bool CCollisionMgr::IsCollide_SAT(const CObj* Obj1, const CObj* Obj2, D3DXVECTOR3* vAxis, float* fMinOverlapped)
bool CCollisionMgr::IsCollide_SAT(CObjYJ * Obj1,CObjYJ* Obj2, D3DXVECTOR3* pOutAxis,
	float* pOutOverlap)
{
	// MTV에 필요한 변수
	float minOverlap = FLT_MAX;
	D3DXVECTOR3 smallestAxis;

	//Obj1 + Obj2 의 모서리를 다 구해서 
	// 각 모서리의 법선 벡터 구하고 이걸 축으로 삼아
	// 각 점들을 이 축에 투영한다. 
	// 범위가 겹치면 다른 모서리에 대해서 수행
	// 겹치지 않으면 충돌 X
	if (Obj2->GetType() != OBJ_MBULLET)
	{
		const auto& vecVertexs1 = Obj1->GetVecWorldVertexs();
		const auto& vecVertexs2 = Obj2->GetVecWorldVertexs();

		vector<D3DXVECTOR3> edges;
		edges.reserve(vecVertexs1.size() + vecVertexs2.size());

		//CObj1의 모서리
		for (size_t i = 0; i < vecVertexs1.size(); ++i) {

			//edges.push_back(*vecVertexs1[i] - *vecVertexs1[(i + 1) % vecVertexs1.size()]);
			edges.push_back(
				*vecVertexs1[(i + 1) % vecVertexs1.size()] - *vecVertexs1[i]);
		}
		//CObj2의 모서리
		for (size_t i = 0; i < vecVertexs2.size(); ++i) {

			//edges.push_back(*vecVertexs2[i] - *vecVertexs2[(i + 1) % vecVertexs2.size()]);
			edges.push_back(
				*vecVertexs2[(i + 1) % vecVertexs2.size()] - *vecVertexs2[i]);
		}

		// 모서리 => 법선 벡터 ( 축 ) 
		for (const auto& e : edges) {

			// edge의 길이가 0이었을경우 normalize의 값이 nan이 되는 경우가 있기 때문에
			// 방지할려는 차원에서 구현한 방어 코드 중요!!!
			{
				float lenSq = e.x * e.x + e.y * e.y;
				if (lenSq < 0.00001f)
					continue;
			}

			D3DXVECTOR3 vAxis;
			vAxis = { -e.y , e.x, 0.f };
			D3DXVec3Normalize(&vAxis, &vAxis);
			float fOutMin1, fOutMax1;
			float fOutMin2, fOutMax2;
			Project(Obj1, vAxis, fOutMin1, fOutMax1);
			Project(Obj2, vAxis, fOutMin2, fOutMax2);

			if (fOutMax1 < fOutMin2 || fOutMax2 < fOutMin1)
				return false;
			float overlap = min(fOutMax1, fOutMax2) - max(fOutMin1, fOutMin2);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				smallestAxis = vAxis;
			}
		}

	}
	else
	{
		const auto& v1 = Obj1->GetVecWorldVertexs();

		if (v1.size() < 2)
			return false;

		D3DXVECTOR3 circleCenter = Obj2->GetPos();
		float radius = 0.f; // ⭐ 공통 인터페이스 권장
		if (Obj2->GetType() == OBJ_MBULLET)
			radius = static_cast<CBullet_YJ*>(Obj2)->GetRadius() * 0.5f;
		float minOverlap = FLT_MAX;
		D3DXVECTOR3 smallestAxis;

		//-------------------------------------
		// 1️⃣ OBB Edge Normal Axis
		//-------------------------------------
		for (size_t i = 0; i < v1.size(); ++i)
		{
			// edge 생성 (vector 안씀)
			D3DXVECTOR3 edge =
				*v1[(i + 1) % v1.size()] - *v1[i];

			float lenSq = edge.x * edge.x + edge.y * edge.y;
			if (lenSq < 0.00001f)
				continue;

			// 법선 축
			D3DXVECTOR3 axis = { -edge.y, edge.x, 0.f };
			D3DXVec3Normalize(&axis, &axis);

			float min1, max1;
			Project(Obj1, axis, min1, max1);

			float centerProj = D3DXVec3Dot(&circleCenter, &axis);

			float min2 = centerProj - radius;
			float max2 = centerProj + radius;

			// 분리축 발견 → 충돌 없음
			if (max1 < min2 || max2 < min1)
				return false;

			float overlap = min(max1, max2) - max(min1, min2);

			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}

		//-------------------------------------
		// ⭐ 2️⃣ 추가 축 (VERY IMPORTANT)
		// Circle Center → OBB Closest Point
		//-------------------------------------

		D3DXVECTOR3 closestPoint = *v1[0];
		float minDistSq = FLT_MAX;

		for (auto v : v1)
		{
			D3DXVECTOR3 diff = circleCenter - *v;
			float distSq = D3DXVec3LengthSq(&diff);

			if (distSq < minDistSq)
			{
				minDistSq = distSq;
				closestPoint = *v;
			}
		}

		D3DXVECTOR3 axis = circleCenter - closestPoint;

		if (D3DXVec3LengthSq(&axis) > 0.00001f)
		{
			D3DXVec3Normalize(&axis, &axis);

			float min1, max1;
			Project(Obj1, axis, min1, max1);

			float centerProj = D3DXVec3Dot(&circleCenter, &axis);
			float min2 = centerProj - radius;
			float max2 = centerProj + radius;

			if (max1 < min2 || max2 < min1)
				return false;

			float overlap = min(max1, max2) - max(min1, min2);

			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}
	}

	
	//MFV 추가해보기
	*pOutAxis = smallestAxis;
	*pOutOverlap = minOverlap;
	return true;
}

void CCollisionMgr::Project(const CObjYJ* Obj, const D3DXVECTOR3 vAxis, float& fOutMin, float& fOutMax)
{

	const auto& vecVertexs = Obj->GetVecWorldVertexs();
	fOutMin = fOutMax = D3DXVec3Dot(vecVertexs[0], &vAxis);


	for (int i = 1; i < vecVertexs.size(); ++i) {

		float fDot = D3DXVec3Dot(vecVertexs[i], &vAxis);
		fOutMin = min(fOutMin, fDot);
		fOutMax = max(fOutMax, fDot);
	}
}