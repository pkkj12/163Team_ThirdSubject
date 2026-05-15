#pragma once
#include "CBase.h"
#include "Engine_Define.h"


BEGIN(Engine)

class _declspec(dllexport) CGraphicDev : public CBase
{
	DECLARE_SINGLETON(CGraphicDev)

private:
	explicit CGraphicDev();
	virtual ~CGraphicDev();

public:
	LPDIRECT3DDEVICE9		Get_GraphicDev() { return m_pGraphicDev; }

public:
	HRESULT			Ready_GraphicDev(HWND hWnd,
		WINMODE eMode,
		const _ulong& iSizeX,
		const _ulong& iSizeY,
		CGraphicDev** ppGraphicDev);

	void			Render_Begin(D3DXCOLOR Color);
	void			Render_End(HWND hWnd = NULL);

private:
	LPDIRECT3D9				m_pSDK;
	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	virtual		void		Free();
};

END