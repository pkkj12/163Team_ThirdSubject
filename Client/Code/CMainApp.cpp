#include "pch.h"
#include "CMainApp.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(CGraphicDev::GetInstance()->Ready_GraphicDev(g_hWnd,
		MODE_WIN, WINCX, WINCY, &m_pDeviceClass)))
		return E_FAIL;

	m_pDeviceClass->AddRef();
	m_pGraphicDev = m_pDeviceClass->Get_GraphicDev();
	m_pGraphicDev->AddRef();

	//return E_FAIL;

	return S_OK;
}

int CMainApp::Update_MainApp(const _float& fTimeDelta)
{
	return 0;
}

void CMainApp::LateUpdate_MainApp(const _float& fTimeDelta)
{
}

void CMainApp::Render_MainApp()
{
	m_pDeviceClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));


	m_pDeviceClass->Render_End();
}

CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if (FAILED(pMainApp->Ready_MainApp()))
	{
		delete pMainApp;
		pMainApp = nullptr;
	}

	return pMainApp;
}

void CMainApp::Free()
{
	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pGraphicDev);

	m_pDeviceClass->DestroyInstance();
}
