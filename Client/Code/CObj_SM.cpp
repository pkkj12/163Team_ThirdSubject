#include "pch.h"
#include "CObj_SM.h"

CObj_SM::CObj_SM() : m_bDead_SM(FALSE), m_fSpeed_SM(0.f)
{
	ZeroMemory(&m_tInfo_SM, sizeof(m_tInfo_SM));
	D3DXMatrixIdentity(&m_tInfo_SM.matWorld);
}

CObj_SM::~CObj_SM()
{
}
