#include "pch.h"
#include "CLine.h"
#include "CScrollMgr.h"

CLine::CLine()
{
}

CLine::CLine(D3DXVECTOR3& tLeft, D3DXVECTOR3& tRight)
	: m_tLine(tLeft, tRight)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tLine.tLeft.x + iScrollX, (int)m_tLine.tLeft.y + iScrollY, NULL);
	LineTo(hDC, (int)m_tLine.tRight.x + iScrollX, (int)m_tLine.tRight.y + iScrollY);
}
