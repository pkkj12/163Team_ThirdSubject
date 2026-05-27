#pragma once

#include "../../Base/CBase.h"
#include "Engine_Define.h"
#include "CGraphicDev.h"
#include "CSceneMgr_.h"

class CObj;

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

public:
	static CMainApp* Create();		// 생성 함수
	virtual void	 Free();		// 소멸 함수

private:
	HDC		m_hDC		= NULL;
	HDC		m_hBackDC	= NULL;
	HBITMAP m_hBMP		= NULL;
	HBITMAP m_hOldBMP	= NULL;
};

