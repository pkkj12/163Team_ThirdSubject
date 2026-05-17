#include "pch.h"
#include "CCollisionMgr.h"


CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;
CCollisionMgr::CCollisionMgr() {}
CCollisionMgr::~CCollisionMgr() {}

void CCollisionMgr::CheckCollision_SAT(YJUTIL::OBJ_TYPE  TYPE1, YJUTIL::OBJ_TYPE  TYPE2)
{
	const auto& ObjList1 = CObjMgr_YJ::GetInstance()->GetObjList(TYPE1);
	const auto& ObjList2 = CObjMgr_YJ::GetInstance()->GetObjList(TYPE2);

	for (auto& Src : ObjList1) {
		for (auto& Dst : ObjList2) {
			D3DXVECTOR3 axis;
			float overlap;
			//충돌 처리  ( 임시 )
			//D3DXVECTOR3 vAxis = { 0, 0, 0 };
			//float fMinOverlapped = static_cast<float>(INF);
			//if (IsCollide_SAT(Src, Dst, &vAxis, &fMinOverlapped)) {
			if (IsCollide_SAT(Src, Dst, &axis, &overlap)) {
				ResolveCollision(Src, Dst, axis, overlap);
				//for (auto& v : Src->GetVecWorldVertexs()) {
				//	cout << " Src : " << v.x << " " << v.y << endl;
				//}
				//for (auto& v : Dst->GetVecWorldVertexs()) {
				//	cout << " Dst : " << v.x << " " << v.y << endl;
				//}

				Src->SetCollide(true);
				Dst->SetCollide(true);
			}
			else {
				Src->SetCollide(false);
				Dst->SetCollide(false);

			}
		}
	}
}

//bool CCollisionMgr::IsCollide_SAT(const CObj* Obj1, const CObj* Obj2, D3DXVECTOR3* vAxis, float* fMinOverlapped)
bool CCollisionMgr::IsCollide_SAT(const CObjYJ * Obj1, const CObjYJ* Obj2, D3DXVECTOR3* pOutAxis,
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