#include "pch.h"
#include "CSpace_JW.h"

CSpace_JW::CSpace_JW()
	: m_dwTime(GetTickCount())
{

}

CSpace_JW::~CSpace_JW()
{

}

void CSpace_JW::Initialize()
{
	m_tWorldInfo.vRotate =
	{
		0.0f,
		0.0f,
		0.f,
	};

	m_tWorldInfo.vDir =
	{
		0.f,
		0.f,
		1.f
	};
}

int CSpace_JW::Update()
{
//	m_tWorldInfo.vRotate.z += 0.1f;
	m_tWorldInfo.vRotate += m_tWorldInfo.vDir * D3DXToRadian(0.314f);

	//if (GetAsyncKeyState('Z'))
	//	m_tWorldInfo.vRotate.y += D3DXToRadian(1.f);
	//if (GetAsyncKeyState('X'))
	//	m_tWorldInfo.vRotate.x += D3DXToRadian(1.f);

	if (GetAsyncKeyState('Z'))
	{
		m_tWorldInfo.vRotate.z -= D3DXToRadian(6.f);
		m_tWorldInfo.vDir.z = -1.f;
	}
	if (GetAsyncKeyState('X'))
	{
		m_tWorldInfo.vRotate.z += D3DXToRadian(6.f);
		m_tWorldInfo.vDir.z = 1.f;
	}

	if (GetAsyncKeyState('A'))
	{
		m_tWorldInfo.vRotate.y -= SPACE_ROT_JW;
	}
	if (GetAsyncKeyState('S'))
	{
		m_tWorldInfo.vRotate.y += SPACE_ROT_JW;
	}

	if (GetAsyncKeyState('Q'))
	{
		m_tWorldInfo.vRotate.x -= SPACE_ROT_JW;
	}
	if (GetAsyncKeyState('W'))
	{
		m_tWorldInfo.vRotate.x += SPACE_ROT_JW;
	}

	if (GetAsyncKeyState('R'))
	{
		m_tWorldInfo.vRotate.x = 0.f;
		m_tWorldInfo.vRotate.y = 0.f;
	}
	
	return 0;
}

void CSpace_JW::LateUpdate()
{
	if (m_dwTime + 10000 < GetTickCount())
	{
		m_tWorldInfo.vDir.z = -m_tWorldInfo.vDir.z;
		m_dwTime = GetTickCount();
	}
}
