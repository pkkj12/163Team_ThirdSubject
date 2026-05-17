#include "pch.h"
#include "CObstacle_JW.h"

#include "CObstacleMgr_JW.h"

CObstacle_JW::CObstacle_JW()
	: m_iSideIDX(0), m_fDistance(0.f), m_fSpeed(0.f)
{
	m_vecLocalVertex.reserve(4);
	m_vecWorldVertex.reserve(4);
}

CObstacle_JW::~CObstacle_JW()
{

}

void CObstacle_JW::Initialize()
{
	// 풀링 쓰려고 세팅하는 거
	if (m_vecLocalVertex.size() == 0)
		for (int i = 0; i < 4; ++i)
			m_vecLocalVertex.push_back(new _vec3{ 0, 0, 0 });

	__super::Initialize_WorldVertex();

	m_iSideIDX = rand() % 6;
//m_iSideIDX = 0;
	m_fDistance = 4.f;
	m_fSpeed = 1.5f;

	//m_vecLocalVertex[0]->x = -SIZE_HEX_JW * RATIO_HEX_X_JW;
	//m_vecLocalVertex[0]->y = -SIZE_HEX_JW;
	//m_vecLocalVertex[1]->x = 0.f;
	//m_vecLocalVertex[1]->y = -SIZE_HEX_JW * RATIO_HEX_Y_JW;

	//m_vecLocalVertex[2]->x = 0.f;
	//m_vecLocalVertex[2]->y = -SIZE_HEX_JW * RATIO_HEX_Y_JW * RATIO_THICK_OBS_JW;
	//m_vecLocalVertex[3]->x = -SIZE_HEX_JW * RATIO_HEX_X_JW * RATIO_THICK_OBS_JW;
	//m_vecLocalVertex[3]->y = -SIZE_HEX_JW * RATIO_THICK_OBS_JW;

	//m_tWorldInfo.vScale = { 1.f, 1.f, 1.f };
	//m_tWorldInfo.vRotate = { 0.f, 0.f, m_iSideIDX * (D3DX_PI / 3.f) };
	//m_tWorldInfo.vPos = { 0.f, 0.f, 0.f };

	m_tWorldInfo.vPos = { 0.f, 0.f, 0.f };
}

int CObstacle_JW::Update()
{
	if (m_bDestory)
		return OBJ_DESTROY_JW;

	m_fDistance -= 0.01f * m_fSpeed;
	m_tWorldInfo.vScale.x = m_fDistance;
	m_tWorldInfo.vScale.y = m_fDistance;

	return 0;
}

void CObstacle_JW::LateUpdate()
{
	if (m_fDistance <= EPSILON_JW)
	{
//		CObstacleMgr_JW::GetInstance()->PushObstacle(this);
		m_bDestory = true;

		return;
	}

	float fOut = m_fDistance + RATIO_THICK_OBS_JW;

	// 밑변 (육각형/플레이어에 닿는 선임)
	m_vecLocalVertex[0]->x = -SIZE_HEX_JW * RATIO_HEX_X_JW * m_fDistance;
	m_vecLocalVertex[0]->y = -SIZE_HEX_JW * m_fDistance;
	m_vecLocalVertex[1]->x = 0.f;                    
	m_vecLocalVertex[1]->y = -SIZE_HEX_JW * RATIO_HEX_Y_JW * m_fDistance;

	// 윗변 (밑변보다 넓은 선)
	m_vecLocalVertex[2]->x = 0.f;                    
	m_vecLocalVertex[2]->y = -SIZE_HEX_JW * RATIO_HEX_Y_JW * fOut;
	m_vecLocalVertex[3]->x = -SIZE_HEX_JW * RATIO_HEX_X_JW * fOut;
	m_vecLocalVertex[3]->y = -SIZE_HEX_JW * fOut;

	_matrix matScale, matRot;
	D3DXMatrixScaling(&matScale, m_tWorldInfo.vScale.x, m_tWorldInfo.vScale.y, 1.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(60.f * m_iSideIDX));

	m_tWorldInfo.matWorld = (matScale * matRot) * m_pParent->GetInfo_JW().matWorld;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(m_vecWorldVertex[i], m_vecLocalVertex[i], &m_tWorldInfo.matWorld);
}

void CObstacle_JW::Render(HDC hDC)
{
	//MoveToEx(hDC, m_vecWorldVertex[0]->x, m_vecWorldVertex[0]->y, NULL);

	//for (int i = 0; i < m_vecWorldVertex.size(); ++i)
	//	LineTo(hDC, m_vecWorldVertex[i]->x, m_vecWorldVertex[i]->y);

	//LineTo(hDC, m_vecWorldVertex[0]->x, m_vecWorldVertex[0]->y);

	POINT pt[4];
	for (int i = 0; i < 4; ++i) 
	{
		pt[i].x = (_long)m_vecWorldVertex[i]->x;
		pt[i].y = (_long)m_vecWorldVertex[i]->y;
	}
	
	HBRUSH hSolidBrush	= CreateSolidBrush(RGB(255, 50 + (m_iSideIDX % 2 * 100), 80));
	HBRUSH hOldBrush	= (HBRUSH)SelectObject(hDC, hSolidBrush);
	HPEN hOldPen		= (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
	
	Polygon(hDC, pt, 4);
	
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hSolidBrush);
}