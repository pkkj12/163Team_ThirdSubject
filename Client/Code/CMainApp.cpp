#include "pch.h"
#include "CMainApp.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
	CSceneMgr_::DestroyInstance();
}

HRESULT CMainApp::Ready_MainApp()
{
	srand(time(NULL));

	m_hDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_hOldBMP = (HBITMAP)SelectObject(m_hBackDC, m_hBMP);

	CSceneMgr_::GetInstance()->Initialize();

	return S_OK;
}


int CMainApp::Update_MainApp(const _float& fTimeDelta)
{
	_int iResult = CSceneMgr_::GetInstance()->Update();



	return 0;
}

void CMainApp::LateUpdate_MainApp(const _float& fTimeDelta)
{
	CSceneMgr_::GetInstance()->LateUpdate();
}

void CMainApp::Render_MainApp()
{
	Rectangle(m_hBackDC, 0, 0, WINCX, WINCY);

	CSceneMgr_::GetInstance()->Render(m_hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY);
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
	SelectObject(m_hBackDC, m_hOldBMP);
	DeleteObject(m_hBMP);
	DeleteDC(m_hBackDC);

	CSceneMgr_::DestroyInstance();
}
