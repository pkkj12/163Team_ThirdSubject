#include "pch.h"
#include "CScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(float fX, float fY)// 배경이미지 값 넣기
{
	if (m_fScrollX > 0.f)
	{
		m_fScrollX = 0.f;
	}
	if (m_fScrollY > 0.f)
	{
		m_fScrollY = 0.f;
	}
	if (WINCX - fX > m_fScrollX)
	{
		m_fScrollX = WINCX - fX;
	}
	if (WINCY - fY > m_fScrollY)
	{
		m_fScrollY = WINCY - fY;
	}
}
