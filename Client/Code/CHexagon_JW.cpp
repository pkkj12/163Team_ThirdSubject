#include "pch.h"
#include "CHexagon_JW.h"
#include "CPlayer_JW.h"

#include "CSpace_JW.h"

CHexagon_JW::CHexagon_JW()
{
	m_vecLocalVertex.reserve(6);
	m_vecWorldVertex.reserve(6);
}

CHexagon_JW::~CHexagon_JW()
{
	Free();
}

void CHexagon_JW::Initialize()
{
	m_vecLocalVertex.push_back(new _vec3
		{
			-SIZE_HEX_JW * RATIO_HEX_X_JW,
			-SIZE_HEX_JW,
			0.f // -SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			0.f,
			-SIZE_HEX_JW * RATIO_HEX_Y_JW,
			0.f // -SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			+SIZE_HEX_JW * RATIO_HEX_X_JW,
			-SIZE_HEX_JW,
			0.f // -SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			+SIZE_HEX_JW * RATIO_HEX_X_JW,
			+SIZE_HEX_JW,
			0.f // -SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			0.f,
			SIZE_HEX_JW * RATIO_HEX_Y_JW,
			0.f // -SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			-SIZE_HEX_JW * RATIO_HEX_X_JW,
			SIZE_HEX_JW,
			0.f // -SIZE_HEX_Z_JW * 0.5f,
		});

	///

	m_vecLocalVertex.push_back(new _vec3
		{
			-SIZE_HEX_JW * RATIO_HEX_X_JW,
			-SIZE_HEX_JW,
			 SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			0.f,
			-SIZE_HEX_JW * RATIO_HEX_Y_JW,
			SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			+SIZE_HEX_JW * RATIO_HEX_X_JW,
			-SIZE_HEX_JW,
			SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			+SIZE_HEX_JW * RATIO_HEX_X_JW,
			+SIZE_HEX_JW,
			SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			0.f,
			SIZE_HEX_JW * RATIO_HEX_Y_JW,
			SIZE_HEX_Z_JW * 0.5f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			-SIZE_HEX_JW * RATIO_HEX_X_JW,
			SIZE_HEX_JW,
			SIZE_HEX_Z_JW * 0.5f,
		});

	m_tLocalInfo.vDir = { 1.f, 0.f, 0.f };

	__super::Initialize_WorldVertex();

	m_tWorldInfo.vPos = { WINCX* 0.5f, WINCY * 0.5f, 0 };

	m_pChild = new CPlayer_JW;
	m_pChild->SetParent_JW(this);
	m_pChild->Initialize();

	m_pParent = new CSpace_JW;
	m_pParent->SetChild_JW(this);
	m_pParent->Initialize();
}

int CHexagon_JW::Update()
{
	// 이 구조는 딱히 권장하지 않음
	m_pParent->Update();

//	m_pChild->Update();

	return 0;
}

void CHexagon_JW::LateUpdate()
{
	_matrix matScale, matRot, matTrans,
		matParentRotX, matParentRotY, matParentRotZ;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRot, m_tWorldInfo.vRotate.z);

	D3DXMatrixRotationX(&matParentRotX, m_pParent->GetInfo_JW().vRotate.x);
	D3DXMatrixRotationY(&matParentRotY, m_pParent->GetInfo_JW().vRotate.y);
	D3DXMatrixRotationZ(&matParentRotZ, m_pParent->GetInfo_JW().vRotate.z);
	matRot = matRot *(matParentRotX * matParentRotY * matParentRotZ);

//	D3DXVec3TransformNormal(&m_tWorldInfo.vDir, &m_tLocalInfo.vDir, &matRot); // 굳이?
	D3DXMatrixTranslation(&matTrans, m_tWorldInfo.vPos.x, m_tWorldInfo.vPos.y, m_tWorldInfo.vPos.z);

	m_tWorldInfo.matWorld = matScale * matRot * matTrans;

	for (int i = 0; i < m_vecLocalVertex.size(); ++i)
		D3DXVec3TransformCoord(m_vecWorldVertex[i], m_vecLocalVertex[i], &m_tWorldInfo.matWorld);

	m_pParent->LateUpdate();

//	m_pChild->LateUpdate();
}

void CHexagon_JW::Render(HDC hDC)
{
	//MoveToEx(hDC, m_vecWorldVertex[0]->x, m_vecWorldVertex[0]->y, NULL);

	//for (int i = 0; i < COUNT_HEX_VTX_JW; ++i)
	//	LineTo(hDC, m_vecWorldVertex[i]->x, m_vecWorldVertex[i]->y);

	//LineTo(hDC, m_vecWorldVertex[0]->x, m_vecWorldVertex[0]->y);

	//for (int i = 0; i < COUNT_HEX_VTX_JW; ++i)
	//{
	//	MoveToEx(hDC, m_vecWorldVertex[i]->x, m_vecWorldVertex[i]->y, NULL);
	//	LineTo(hDC, m_vecWorldVertex[i + COUNT_HEX_VTX_JW]->x, m_vecWorldVertex[i + COUNT_HEX_VTX_JW]->y);
	//}

	//for (int i = 0; i < COUNT_HEX_VTX_JW; ++i)
	//	LineTo(hDC, m_vecWorldVertex[i + COUNT_HEX_VTX_JW]->x, m_vecWorldVertex[i + COUNT_HEX_VTX_JW]->y);

	/// 색으로 한 번 ㄱㄱ ///

	POINT ptPolygon[COUNT_HEX_VTX_JW];
	for (int i = 0; i < COUNT_HEX_VTX_JW; ++i)
	{
		ptPolygon[i].x = (_long)m_vecWorldVertex[i]->x;
		ptPolygon[i].y = (_long)m_vecWorldVertex[i]->y;
	}

	HBRUSH  hSolidBrush = CreateSolidBrush(RGB(255, 100, 100));
	HBRUSH	hOldBrush = (HBRUSH)SelectObject(hDC, hSolidBrush);

	Polygon(hDC, ptPolygon, COUNT_HEX_VTX_JW);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hSolidBrush);

	//for (int i = 0; i < COUNT_HEX_VTX_JW; ++i)
	//{
	//	ptPolygon[i].x = (_long)m_vecWorldVertex[i + COUNT_HEX_VTX_JW]->x;
	//	ptPolygon[i].y = (_long)m_vecWorldVertex[i + COUNT_HEX_VTX_JW]->y;
	//}

	//hSolidBrush = CreateSolidBrush(RGB(255, 50, 0));
	//hOldBrush = (HBRUSH)SelectObject(hDC, hSolidBrush);

	//Polygon(hDC, ptPolygon, COUNT_HEX_VTX_JW);

	//SelectObject(hDC, hOldBrush);
	//DeleteObject(hSolidBrush);

	//POINT ptPolygon_Side[4];

	//for (int j = 0; j < 5; ++j)
	//{
	//	MoveToEx(hDC, m_vecWorldVertex[j + 6]->x, m_vecWorldVertex[j + 6]->y, NULL);

	//	ptPolygon_Side[0].x = (_long)m_vecWorldVertex[j + 6]->x;
	//	ptPolygon_Side[0].y = (_long)m_vecWorldVertex[j + 6]->y;

	//	ptPolygon_Side[1].x = (_long)m_vecWorldVertex[j + 7]->x;
	//	ptPolygon_Side[1].y = (_long)m_vecWorldVertex[j + 7]->y;

	//	ptPolygon_Side[2].x = (_long)m_vecWorldVertex[j + 1]->x;
	//	ptPolygon_Side[2].y = (_long)m_vecWorldVertex[j + 1]->y;

	//	ptPolygon_Side[3].x = (_long)m_vecWorldVertex[j + 0]->x;
	//	ptPolygon_Side[3].y = (_long)m_vecWorldVertex[j + 0]->y;

	//	hSolidBrush = CreateSolidBrush(RGB(255, 50 + ((j + 1) % 2) * 100, 80));
	//	hOldBrush = (HBRUSH)SelectObject(hDC, hSolidBrush);

	//	Polygon(hDC, ptPolygon_Side, 4);

	//	SelectObject(hDC, hOldBrush);
	//	DeleteObject(hSolidBrush);
	//}

	//MoveToEx(hDC, m_vecWorldVertex[0 + 6]->x, m_vecWorldVertex[0 + 6]->y, NULL);

	//ptPolygon_Side[0].x = (_long)m_vecWorldVertex[5 + 6]->x;
	//ptPolygon_Side[0].y = (_long)m_vecWorldVertex[5 + 6]->y;

	//ptPolygon_Side[1].x = (_long)m_vecWorldVertex[5 + 0]->x;
	//ptPolygon_Side[1].y = (_long)m_vecWorldVertex[5 + 0]->y;

	//ptPolygon_Side[2].x = (_long)m_vecWorldVertex[0]->x;
	//ptPolygon_Side[2].y = (_long)m_vecWorldVertex[0]->y;

	//ptPolygon_Side[3].x = (_long)m_vecWorldVertex[5]->x;
	//ptPolygon_Side[3].y = (_long)m_vecWorldVertex[5]->y;

	//hSolidBrush = CreateSolidBrush(RGB(255, 50 + 100, 80));
	//hOldBrush = (HBRUSH)SelectObject(hDC, hSolidBrush);

	//Polygon(hDC, ptPolygon_Side, 4);

	//SelectObject(hDC, hOldBrush);
	//DeleteObject(hSolidBrush);

	// 6 7 1 0
	// 

	m_pParent->Render(hDC);
//	m_pChild->Render(hDC);
}

void CHexagon_JW::Free()
{
	// Safe_Release<CObj_JW*>(m_pChild);
	// Safe_Delete<CObj_JW*>(m_pChild);

	// 부모를 나중에? 근데 이렇게 하는게 맞나 싶긴 하네
	// Safe_Release<CObj_JW*>(m_pParent);
	Engine::Safe_Delete<CObj_JW*>(m_pParent);
}
