#include "pch.h"
#include "CScrollMgr_YJ.h"

CScrollMgr_YJ* CScrollMgr_YJ::m_pInstance = nullptr;

CScrollMgr_YJ::CScrollMgr_YJ() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollMgr_YJ::~CScrollMgr_YJ()
{
}

void CScrollMgr_YJ::Scroll_Lock(float fX, float fY)// 배경이미지 값 넣기
{
	m_bLockX = false;
	m_bLockY = false;

	float minScrollX = WINCX - fX;
	float minScrollY = WINCY - fY;

	if (m_fScrollX > 0.f)
	{
		m_fScrollX = 0.f;
		m_bLockX = true;
	}
	if (m_fScrollX < minScrollX)
	{
		m_fScrollX = minScrollX;
		m_bLockX = true;
	}
	if (m_fScrollY > 0.f)
	{
		m_fScrollY = 0.f;
		m_bLockY = true;
	}

	if (m_fScrollY < minScrollY)
	{
		m_fScrollY = minScrollY;
		m_bLockY = true;
	}
}