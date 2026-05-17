#include "pch.h"
#include "CKeyMgr_SM.h"

CKeyMgr_SM* CKeyMgr_SM::m_pInstance = nullptr;

CKeyMgr_SM::CKeyMgr_SM()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr_SM::~CKeyMgr_SM()
{
}

bool CKeyMgr_SM::Key_Pressing(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;
	
	return false;
}

// 이전에 누른 적이 있고, 지금 막 뗐을 때
bool CKeyMgr_SM::Key_Up(int iKey)
{
	if ((m_bKeyState[iKey]) && !(GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	return false;
}
// 이전에 누른 적이 없고, 지금 막 눌렀을 때
bool CKeyMgr_SM::Key_Down(int iKey)
{
	if ((!m_bKeyState[iKey]) && (GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	return false;
}

void CKeyMgr_SM::Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
		{
			m_bKeyState[i] = !m_bKeyState[i];
		}

		if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
		{
			m_bKeyState[i] = !m_bKeyState[i];
		}
	}
}
