#include "pch.h"
#include "CShield_YJ.h"
#include "CTimeMgr_YJ.h"
#include "CScrollMgr_YJ.h"
CShield_YJ::CShield_YJ()
{
}

CShield_YJ::~CShield_YJ()
{
}

HRESULT CShield_YJ::Ready()
{
	
	return S_OK;
}

int CShield_YJ::Update()
{
	RotateAroundPlayer();

	//D3DXMATRIX		matScale, matRotZ, matTrans;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	return 0;
}

void CShield_YJ::LateUpdate()
{
}

void CShield_YJ::Render(HDC hDC)
{
	float fScrollX = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollX();
	float fScrollY = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollY();
	Ellipse(hDC,
		m_tInfo.vPos.x - SHIELD_RADIUS * 0.5f - fScrollX,
		m_tInfo.vPos.y - SHIELD_RADIUS * 0.5f - fScrollY,
		m_tInfo.vPos.x + SHIELD_RADIUS * 0.5f - fScrollX,
		m_tInfo.vPos.y + SHIELD_RADIUS * 0.5f - fScrollY
	);
}

void CShield_YJ::Free()
{
}

void CShield_YJ::RotateAroundPlayer()
{
	m_fAngle += m_fRotSpeed * 100.f * fDT;

	float rad = D3DXToRadian(m_fAngle);

	D3DXVECTOR3 vOwnerPos = m_pOwner->GetInfo().vPos;

	m_tInfo.vDir.x = cosf(rad);
	m_tInfo.vDir.y = sinf(rad);
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos = vOwnerPos + m_tInfo.vDir * m_fRadius;
}
