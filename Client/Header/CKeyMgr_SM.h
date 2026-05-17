#pragma once

#include "Define_SM.h"

class CKeyMgr_SM
{
private:
	CKeyMgr_SM();
	CKeyMgr_SM(const CKeyMgr_SM& rhs) = delete;
	CKeyMgr_SM& operator=(CKeyMgr_SM& rKeyMgr) = delete;
	~CKeyMgr_SM();

public:
	bool		Key_Pressing(int iKey);
	bool		Key_Up(int iKey);		// ´­·¶´Ù°¡ ¶ÃÀ» ¶§
	bool		Key_Down(int iKey);		// ¸· ´­·¶À» ¶§ ÇÑ ¹ø¸¸ 

	void		Update();

public:
	static CKeyMgr_SM* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr_SM;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyMgr_SM* m_pInstance;
	bool	m_bKeyState[VK_MAX];

};

