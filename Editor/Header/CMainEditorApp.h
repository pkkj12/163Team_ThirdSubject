#pragma once

#include "CBase.h"

class CMainEditorApp
	: public CBase
{
public:
	explicit CMainEditorApp();
	virtual ~CMainEditorApp();

public:
	HRESULT			Ready_MainApp();
	int				Update_MainApp(const float& fTimeDelta);
	void			LateUpdate_MainApp(const float& fTimeDelta);
	void			Render_MainApp();


public:
	static CMainEditorApp* Create();
private:
	virtual void Free();
private:
	HDC		m_hDC;
};

