#include "pch.h"
#include "CScene_YJ.h"

#include "CVampSurvival.h"

void CScene_YJ::Initialize()
{
	m_pVS = new CVampSurvival();
	m_pVS->Initialize();
}

int CScene_YJ::Update()
{
	m_pVS->Update();

	return 0;
}

void CScene_YJ::LateUpdate()
{
	m_pVS->LateUpdate();
}

void CScene_YJ::Render(HDC hMemDC)
{
	m_pVS->Render(hMemDC);
}

void CScene_YJ::Release()
{
	::Safe_Delete(m_pVS);
}
