#include "pch.h"
#include "CBullet_YJ.h"
#include "CScrollMgr_YJ.h"
#include "CTimeMgr_YJ.h"

CBullet_YJ::CBullet_YJ()
{
}

CBullet_YJ::~CBullet_YJ()
{
}

HRESULT CBullet_YJ::Ready()
{
    m_fSpeed = 500.f;
    return S_OK;
}

int CBullet_YJ::Update()
{
	if (GetCollide()) 
		return OBJ_DEAD;
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * fDT;
	__super::MakeWorldMatrix();
	__super::UpdateWorldVertex();
    return OBJ_NOEVENT;
}

void CBullet_YJ::LateUpdate()
{
}

void CBullet_YJ::Render(HDC hDC)
{
	float fScrollX = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollX();
	float fScrollY = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollY();
	Ellipse(hDC,
		m_tInfo.vPos.x - BULLET_RADIUS * 0.5f - fScrollX,
		m_tInfo.vPos.y - BULLET_RADIUS * 0.5f - fScrollY,
		m_tInfo.vPos.x + BULLET_RADIUS * 0.5f - fScrollX,
		m_tInfo.vPos.y + BULLET_RADIUS * 0.5f - fScrollY
	);
}

void CBullet_YJ::Free()
{
}
