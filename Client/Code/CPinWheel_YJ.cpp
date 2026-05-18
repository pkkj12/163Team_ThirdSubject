#include "pch.h"
#include "CPinWheel_YJ.h"
#include "CTimeMgr_YJ.h"
#include "CObjMgr_YJ.h"
#include "CPlayer_YJ.h"
CPinWheel_YJ::CPinWheel_YJ()
{
}

CPinWheel_YJ::~CPinWheel_YJ()
{
}

HRESULT CPinWheel_YJ::Ready()
{
	m_fSpeed = 10.f;
	return S_OK;
}

int CPinWheel_YJ::Update()
{
	//Vec2 pos = { m_tInfo.fX, m_tInfo.fY };
	bool bNowCollide = GetCollide();
	if (bNowCollide)
	{
		return OBJ_DEAD;
	}
	m_vWorldAngle.z -= 30.f * fDT;
	m_fDistance += m_fSpeed * fDT;

	float rad = D3DXToRadian(m_vWorldAngle.z);

	D3DXVECTOR3 dir(
		cosf(rad),
		sinf(rad),
		0.f);
	D3DXVECTOR3 pos = m_tInfo.vPos + dir * m_fDistance;

	SetPos(pos);
	//D3DXMATRIX vDir;


	//pos = m_fDistance * Utils::GetDirection(m_fAngle) + bossPos;

	//Set_Pos(pos.x, pos.y);
	__super::MakeWorldMatrix();
	__super::UpdateWorldVertex();

	/*if (m_t.x < 0 || pos.x > WINCY || pos.y < 0)
	{
		return OBJ_DEAD;
	}*/
	return OBJ_NOEVENT;
}

void CPinWheel_YJ::LateUpdate()
{
}

void CPinWheel_YJ::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CPinWheel_YJ::Free()
{
}

void CPinWheel_YJ::SetCollide(CObjYJ* pObj)
{
	if (!static_cast<CPlayer_YJ*>(GET_SINGLE(CObjMgr_YJ)->GetPlayer())->IsGod()
		&& pObj->GetType() == OBJ_PLAYER)
	{
		static_cast<CPlayer_YJ*>(GET_SINGLE(CObjMgr_YJ)->GetPlayer())->SetGod(true);
		static_cast<CPlayer_YJ*>(GET_SINGLE(CObjMgr_YJ)->GetPlayer())->SetHP(1);
	}
}
