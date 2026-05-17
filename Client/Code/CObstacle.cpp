#include "pch.h"
#include "CObstacle.h"
#include "CLine_YJ.h"
#include "CScrollMgr_YJ.h"

CObstacle::CObstacle()
{
}

CObstacle::~CObstacle()
{
}

HRESULT CObstacle::Ready()
{
	for (int i = 0; i < m_vecOriginVertex.size(); ++i)
		m_vecVertex.push_back(new D3DXVECTOR3);
    return S_OK;
}

int CObstacle::Update()
{
	__super::MakeWorldMatrix();
	__super::UpdateWorldVertex();
    return OBJ_NOEVENT;
}

void CObstacle::LateUpdate()
{

}

void CObstacle::Render(HDC hDC)
{
	//for (auto line : m_vecLines)
	//{
	//	line->Render(hDC);
	//}

	if (m_vecVertex.empty())
		return;

	float m_fScrollX = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollX();
	float m_fScrollY = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollY();
	MoveToEx(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY, nullptr);
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		LineTo(hDC, m_vecVertex[i]->x - m_fScrollX, m_vecVertex[i]->y - m_fScrollY);
	}
	LineTo(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY);
}

void CObstacle::Free()
{
}
