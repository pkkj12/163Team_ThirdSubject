#pragma once

#include "../../Base/CBase.h"
#include "Engine_Define.h"
#include "CGraphicDev.h"

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
	HDC		m_hDC		= NULL;
	HDC		m_hBackDC	= NULL;
	HBITMAP m_hBMP		= NULL;
	HBITMAP m_hOldBMP	= NULL;
};

