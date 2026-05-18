#include "pch.h"
#include "CPlayer_YJ.h"
#include "CShield_YJ.h"
#include "CScrollMgr_YJ.h"
#include "CTimeMgr_YJ.h"

CPlayer_YJ::CPlayer_YJ() : m_vecPosin{}, m_pShield(nullptr), m_iLife(5), m_bDead(false), m_fGodTime(0.f)
, m_bGod(false), m_fFadeTime(0.f), m_fDistance(0.f)
{
	m_vecOriginVertex.reserve(4);
	m_vecVertex.reserve(4);
}

CPlayer_YJ::~CPlayer_YJ()
{
}

HRESULT CPlayer_YJ::Ready()
{

	m_tInfo.vPos = { 400.f,300.f,0.f };
	m_tInfo.vLook = { 0.f , -1.f, 0.f };

	//m_tOriginInfo = m_tInfo;

	m_vecOriginVertex.push_back(new _vec3(-SIZE_RECTANGLE * 0.5f, -DISTANCE, 0.f));
	m_vecOriginVertex.push_back(new _vec3(SIZE_RECTANGLE * 0.5f, -DISTANCE, 0.f));
	m_vecOriginVertex.push_back(new _vec3(SIZE_RECTANGLE * 0.5f, DISTANCE, 0.f));
	m_vecOriginVertex.push_back(new _vec3(-SIZE_RECTANGLE * 0.5f, DISTANCE, 0.f));

	for (int i = 0; i < m_vecOriginVertex.size(); ++i)
		m_vecVertex.push_back(new D3DXVECTOR3);

	m_vecPosin = { 0.f, - 20.f, 0.f};
	m_vecOriginalPosin = m_vecPosin;


	if (!m_pShield)
	{
		m_pShield = new CShield_YJ;
		dynamic_cast<CShield_YJ*>(m_pShield)->SetOwner(this);
	}

	return S_OK;
}

int CPlayer_YJ::Update()
{
	if (m_iLife <= 0)
		m_bDead = true;
	if (m_bGod)
	{
		m_fGodTime += fDT;
		m_fFadeTime += fDT;

		if (m_fFadeTime >= 0.4f)
			m_fFadeTime = 0.f;
	}

	if (m_fGodTime >= 3.f)
	{
		m_bGod = false;
		m_fGodTime = 0;
		m_fFadeTime = 0;
	}
		

	Key_Input();
	OffSet();
	m_pShield->Update();

	__super::MakeWorldMatrix();
	__super::UpdateWorldVertex();
	return NOEVENT;
}

void CPlayer_YJ::LateUpdate()
{
	//D3DXMATRIX matScale, matRotZ,matTrans;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);	// 크기
	//D3DXMatrixRotationZ(&matRotZ, m_vWorldAngle.z);	// Z축 기준 회전
	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &matRotZ);

	//D3DXMatrixTranslation(&matTrans
	//	, m_tInfo.vPos.x
	//	, m_tInfo.vPos.y
	//	, m_tInfo.vPos.z); // 이동
	////m_tInfo.matWorld = matScale * matRotZ * matTrans;		// world 변환
	//m_tInfo.matWorld = matScale * matRotZ * matTrans;
	//for (int i = 0; i < m_vecVertex.size(); ++i)
	//{
	//	//m_vecVertex[i] = m_vecOriginVertex[i];
	//	D3DXVec3TransformCoord(m_vecVertex[i], m_vecOriginVertex[i], &m_tInfo.matWorld);
	//}
	m_vecPosin = m_vecOriginalPosin;
	//m_vecPosin += m_vWorldTrans;
	D3DXVec3TransformCoord(&m_vecPosin, &m_vecPosin, &m_tInfo.matWorld);


	m_pShield->LateUpdate();
}

void CPlayer_YJ::Render(HDC hDC)
{
	float m_fScrollX = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollX();
	float m_fScrollY = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollY();

	if (!m_bGod)
	{
		MoveToEx(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY, nullptr);
		for (size_t i = 0; i < m_vecVertex.size(); ++i)
		{
			LineTo(hDC, m_vecVertex[i]->x - m_fScrollX, m_vecVertex[i]->y - m_fScrollY);
		}
		LineTo(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY);

		MoveToEx(hDC, m_tInfo.vPos.x - m_fScrollX, m_tInfo.vPos.y - m_fScrollY, NULL);
		LineTo(hDC, m_vecPosin.x - m_fScrollX, m_vecPosin.y - m_fScrollY);

		m_pShield->Render(hDC);
	}
	else
	{
		if (m_fFadeTime > 0.2f)
		{
			MoveToEx(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY, nullptr);
			for (size_t i = 0; i < m_vecVertex.size(); ++i)
			{
				LineTo(hDC, m_vecVertex[i]->x - m_fScrollX, m_vecVertex[i]->y - m_fScrollY);
			}
			LineTo(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY);

			MoveToEx(hDC, m_tInfo.vPos.x - m_fScrollX, m_tInfo.vPos.y - m_fScrollY, NULL);
			LineTo(hDC, m_vecPosin.x - m_fScrollX, m_vecPosin.y - m_fScrollY);

		}
	}
	m_pShield->Render(hDC);
}

void CPlayer_YJ::Free()
{
}

void CPlayer_YJ::SetCollide(CObjYJ* pObj)
{
	//if (!m_bGod && pObj->GetType() == OBJ_MBULLET)
	//{
	//	m_bGod = true;
	//}
}

void CPlayer_YJ::OffSet()
{
	float fMinX = 100;
	float fMaxX = WINCX - 100;


	float fMinY = 80.f;
	float fMaxY = WINCY - 80.f;

	float fScrollX = CScrollMgr_YJ::GetInstance()->Get_ScrollX();
	float fScrollY = CScrollMgr_YJ::GetInstance()->Get_ScrollY();
	// 플레이어 화면 좌표
	float fScreenX = m_tInfo.vPos.x - fScrollX;
	float fScreenY = m_tInfo.vPos.y - fScrollY;

	if (!CScrollMgr_YJ::GetInstance()->IsLockX())
	{
		if (fScreenX < fMinX)
			CScrollMgr_YJ::GetInstance()->Set_ScrollX(fScreenX - fMinX);

		else if (fScreenX > WINCX - 100.f)
			CScrollMgr_YJ::GetInstance()->Set_ScrollX(fScreenX - fMaxX);
	}

	if (!CScrollMgr_YJ::GetInstance()->IsLockY())
	{
		if (fScreenY < fMinY)
			CScrollMgr_YJ::GetInstance()->Set_ScrollY(fScreenY - fMinY);

		else if (fScreenY > fMaxY)
			CScrollMgr_YJ::GetInstance()->Set_ScrollY(fScreenY - fMaxY);

	}

	//if (fMinX > fScreenX)
	//{
	//	CScrollMgr_YJ::GetInstance()->Set_ScrollX(-(fMinX - fScreenX));
	//}

	//else if (fMaxX < fScreenX)
	//{
	//	CScrollMgr_YJ::GetInstance()->Set_ScrollX(fScreenX - fMaxX);
	//}

	//// Y
	//if (fScreenY < fMinY)
	//	CScrollMgr_YJ::GetInstance()->Set_ScrollY(-(fMinY - fScreenY));
	//else if (fScreenY > fMaxY)
	//	CScrollMgr_YJ::GetInstance()->Set_ScrollY(fScreenY - fMaxY);
}

void CPlayer_YJ::Key_Input()
{


	if (GetAsyncKeyState('A'))
	{
		m_vWorldAngle.z -= 0.1f;
	}
	if (GetAsyncKeyState('D'))
	{
		m_vWorldAngle.z += 0.1f;
	}

	if (GetAsyncKeyState('J'))
	{
		m_vWorldAngle.x += 0.1f;
	}
	if (GetAsyncKeyState('K'))
	{
		m_vWorldAngle.y += 0.1f;
	}

	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, m_vWorldAngle.z);

	D3DXVec3TransformNormal(
		&m_tInfo.vDir,
		&m_tInfo.vLook,
		&matRot);

	if (GetAsyncKeyState('W'))
	{
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * 3.f;
	}
	if (GetAsyncKeyState('S'))
	{
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * 3.f;
	}

}
