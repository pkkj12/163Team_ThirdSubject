#include "pch.h"
#include "CMainApp.h"

//Test Include
#include "CPlayer_SM.h"
#include "CMonster_SM.h"
//

CMainApp::CMainApp() : m_pPlayer_SM(nullptr)
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


	//testCode
	if (!m_pPlayer_SM)
	{
		m_pPlayer_SM = new CPlayer_SM;
		m_pPlayer_SM->Initialize();
	}

	m_hDC_SM		= GetDC(g_hWnd);
	m_hBackDC_SM	= CreateCompatibleDC(m_hDC_SM);
	m_hBMP_SM		= CreateCompatibleBitmap(m_hDC_SM, WINCX, WINCY);
	m_hOldBMP_SM	= (HBITMAP)SelectObject(m_hBackDC_SM, m_hBMP_SM);

	//
	//return E_FAIL;

	return S_OK;
}

int CMainApp::Update_MainApp(const _float& fTimeDelta)
{
	m_pPlayer_SM->Update();



	return 0;
}

void CMainApp::LateUpdate_MainApp(const _float& fTimeDelta)
{
	m_pPlayer_SM->Late_Update();
}

void CMainApp::Render_MainApp()
{
	Rectangle(m_hBackDC_SM, 0, 0, WINCX, WINCY);

	//CSceneMgr_SM::GetInstance()->Render(m_hBackDC_SM);
	m_pPlayer_SM->Render(m_hBackDC_SM);

	BitBlt(m_hDC_SM, 0, 0, WINCX, WINCY, m_hBackDC_SM, 0, 0, SRCCOPY);

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
