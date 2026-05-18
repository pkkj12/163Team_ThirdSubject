#include "pch.h"
#include "CMainApp.h"
#include "CVampSurvival.h"
CMainApp::CMainApp() : m_hDC(nullptr), m_pSceneYJ(nullptr)
{
}

CMainApp::~CMainApp()
{
}



HRESULT CMainApp::Ready_MainApp()
{

	m_hDC = GetDC(g_hWnd);

	m_hDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_hOldBMP = (HBITMAP)SelectObject(m_hBackDC, m_hBMP);
	//if (FAILED(CGraphicDev::GetInstance()->Ready_GraphicDev(g_hWnd,
	//	MODE_WIN, WINCX, WINCY, &m_pDeviceClass)))
	//	return E_FAIL;

	//m_pDeviceClass->AddRef();
	//m_pGraphicDev = m_pDeviceClass->Get_GraphicDev();
	//m_pGraphicDev->AddRef();

	//return E_FAIL;
	if (!m_pSceneYJ)
	{
		m_pSceneYJ = new CVampSurvival;
		m_pSceneYJ->Initialize();
	}

	return S_OK;
}


int CMainApp::Update_MainApp(const _float& fTimeDelta)
{
	m_pSceneYJ->Update();
	return 0;
}

void CMainApp::LateUpdate_MainApp(const _float& fTimeDelta)
{
	m_pSceneYJ->LateUpdate();
}

void CMainApp::Render_MainApp()
{

	Rectangle(m_hBackDC, 0, 0, WINCX, WINCY);


	m_pSceneYJ->Render(m_hBackDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY);

	//m_pDeviceClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	//m_pDeviceClass->Render_End();
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
	//Safe_Release(m_pDeviceClass);
	//Safe_Release(m_pGraphicDev);

	//m_pDeviceClass->DestroyInstance();
}
