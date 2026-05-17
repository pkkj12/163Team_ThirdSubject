#include "pch.h"
#include "CLine_YJ.h"
#include "CScrollMgr_YJ.h"

CLine_YJ::CLine_YJ()
{
}

CLine_YJ::CLine_YJ(D3DXVECTOR3& tLeft, D3DXVECTOR3& tRight)
	: m_tLine(tLeft, tRight)
{
}

CLine_YJ::~CLine_YJ()
{
}

void CLine_YJ::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr_YJ::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr_YJ::GetInstance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tLine.tLeft.x - iScrollX, (int)m_tLine.tLeft.y - iScrollY, NULL);
	LineTo(hDC, (int)m_tLine.tRight.x - iScrollX, (int)m_tLine.tRight.y - iScrollY);
}
