#include "pch.h"
#include "CPlayer_JW.h"

CPlayer_JW::CPlayer_JW()
{

}

CPlayer_JW::~CPlayer_JW()
{

}

void CPlayer_JW::Initialize()
{
	m_vecLocalVertex.push_back(new _vec3
		{
			-SIZE_TRIANGLE_JW * 0.5f,
			-(DISTANCE_TRIANGLE_JW),
			0.f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			0.f,
			-(SIZE_TRIANGLE_JW + DISTANCE_TRIANGLE_JW),
			0.f,
		});

	m_vecLocalVertex.push_back(new _vec3
		{
			+SIZE_TRIANGLE_JW * 0.5f,
			-(DISTANCE_TRIANGLE_JW),
			0.f,
		});

	__super::Initialize_WorldVertex();

	m_tWorldInfo.vPos = m_pParent->GetInfo_JW().vPos;
}

int CPlayer_JW::Update()
{
	Key_Input();

	return 0;
}

void CPlayer_JW::LateUpdate()
{
	_matrix matScale, matRot, matTrans,
		matParentRotX, matParentRotY, matParentRotZ;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRot, m_tWorldInfo.vRotate.z);

	D3DXMatrixRotationX(&matParentRotX, m_pParent->GetParent_JW()->GetInfo_JW().vRotate.x);
	D3DXMatrixRotationY(&matParentRotY, m_pParent->GetParent_JW()->GetInfo_JW().vRotate.y);
	D3DXMatrixRotationZ(&matParentRotZ, m_pParent->GetParent_JW()->GetInfo_JW().vRotate.z);
	matRot = matRot * (matParentRotX * matParentRotY * matParentRotZ);

	D3DXVec3TransformNormal(&m_tWorldInfo.vDir, &m_tLocalInfo.vDir, &matRot); // ±ª¿Ã?
	D3DXMatrixTranslation(&matTrans, m_tWorldInfo.vPos.x, m_tWorldInfo.vPos.y, m_tWorldInfo.vPos.z);

	m_tWorldInfo.matWorld = matScale * matRot * matTrans;

	for (int i = 0; i < m_vecLocalVertex.size(); ++i)
		D3DXVec3TransformCoord(m_vecWorldVertex[i], m_vecLocalVertex[i], &m_tWorldInfo.matWorld);
}

void CPlayer_JW::Render(HDC hDC)
{
	MoveToEx(hDC, m_vecWorldVertex[0]->x, m_vecWorldVertex[0]->y, NULL);

	for (int i = 0; i < m_vecWorldVertex.size(); ++i)
		LineTo(hDC, m_vecWorldVertex[i]->x, m_vecWorldVertex[i]->y);

	LineTo(hDC, m_vecWorldVertex[0]->x, m_vecWorldVertex[0]->y);

#ifdef _DEBUG
	DBG_WindowText();
#endif
}

void CPlayer_JW::Key_Input()
{
	if (GetAsyncKeyState(VK_LEFT))
		m_tWorldInfo.vRotate.z -= 0.06f;
	if (GetAsyncKeyState(VK_RIGHT))
		m_tWorldInfo.vRotate.z += 0.06f;
}

#ifdef _DEBUG
void CPlayer_JW::DBG_WindowText()
{
	float fRotZ = fmodf(D3DXToDegree(m_tWorldInfo.vRotate.z), 360.f);
	_uint iIndex = (_uint)(fRotZ / 60.f);
	SetWindowText(g_hWnd, to_wstring(iIndex).c_str());
}
#endif