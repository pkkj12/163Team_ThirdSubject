#pragma once

#include "../../Base/CBase.h"
#include "Engine_Define.h"
#include "CGraphicDev.h"

class CObj_SM;

class CMainApp
	: public CBase
{	
public:
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT			Ready_MainApp();
	int				Update_MainApp(const _float& fTimeDelta);
	void			LateUpdate_MainApp(const _float& fTimeDelta);
	void			Render_MainApp();
private:
	Engine::CGraphicDev* m_pDeviceClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static CMainApp* Create();		// 생성 함수
	virtual void	 Free();		// 소멸 함수

private:
	CObj_SM*	m_pPlayer_SM;
	CObj_SM*	m_pMonster_SM;

	HDC			m_hDC_SM		= NULL;
	HDC			m_hBackDC_SM	= NULL;
	HBITMAP		m_hBMP_SM		= NULL;
	HBITMAP		m_hOldBMP_SM	= NULL;
};

