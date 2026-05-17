#include "CMonster_SM.h"
#include "Define_SM.h"

CMonster_SM::CMonster_SM()
{
}

CMonster_SM::~CMonster_SM()
{
}



void CMonster_SM::Initialize()
{
	m_tInfo_SM.vPos = { WINCX >> 1, WINCY >> 1, 0.f };

	m_tInfo_SM.vDir = { 1.f, 0.f, 0.f };
	m_tInfo_SM.vLook = { 1.f, 0.f, 0.f };

	m_fSpeed_SM = 5.f;
	m_fAngle_SM = 0.f;

	vecOriginPlayerVertex.push_back(new _vec3{ -50,		-50,	0 });
	vecOriginPlayerVertex.push_back(new _vec3{ 50,		-50,	0 });
	vecOriginPlayerVertex.push_back(new _vec3{ 50,		50,		0 });
	vecOriginPlayerVertex.push_back(new _vec3{ -50,		50,		0 });

	vecTransformPlayerVertex.push_back(new _vec3{ -50,	-50,	0 });
	vecTransformPlayerVertex.push_back(new _vec3{ 50,	-50,	0 });
	vecTransformPlayerVertex.push_back(new _vec3{ 50,	50,		0 });
	vecTransformPlayerVertex.push_back(new _vec3{ -50,	50,		0 });
}

int CMonster_SM::Update()
{
	if (m_bDead_SM == TRUE)
	{
		return OBJ_DEAD_SM;
	}

	_matrix matScale_SM, matRotation_SM, matTrans_SM;
	D3DXMatrixIdentity(&m_tInfo_SM.matWorld);

	D3DXMatrixScaling(&matScale_SM, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotation_SM, m_fAngle_SM);
	D3DXMatrixTranslation(&matTrans_SM, m_tInfo_SM.vPos.x, m_tInfo_SM.vPos.y, m_tInfo_SM.vPos.z);

	m_tInfo_SM.matWorld = matScale_SM * matRotation_SM * matTrans_SM;

	return OBJ_NOEVENT_SM;
}

void CMonster_SM::Late_Update()
{
	vector<_vec3*>::iterator OriginIter = vecOriginPlayerVertex.begin();
	vector<_vec3*>::iterator TransformIter = vecTransformPlayerVertex.begin();

	int iSize = vecOriginPlayerVertex.size();

	for (int i = 0; i < iSize; ++i)
	{
		D3DXVec3TransformCoord((*TransformIter), (*OriginIter), &m_tInfo_SM.matWorld);

		++OriginIter;
		++TransformIter;
	}
}

void CMonster_SM::Render(HDC hDC)
{
	MoveToEx(hDC, vecTransformPlayerVertex.front()->x, vecTransformPlayerVertex.front()->y, nullptr);

	for (auto&& iter = vecTransformPlayerVertex.begin(); iter != vecTransformPlayerVertex.end(); ++iter)
	{
		LineTo(hDC, (*iter)->x, (*iter)->y);
	}

	LineTo(hDC, vecTransformPlayerVertex.front()->x, vecTransformPlayerVertex.front()->y);
}

void CMonster_SM::Release()
{
}
