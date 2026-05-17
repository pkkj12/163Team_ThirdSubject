#include "pch.h"
#include "CMainEditorApp.h"
#include "CLineMgr.h"	
#include "CScrollMgr.h"
#include "CKeyMgr.h"

CMainEditorApp::CMainEditorApp() : m_hDC(nullptr)
{
}

CMainEditorApp::~CMainEditorApp()
{
}


HRESULT	CMainEditorApp::Ready_MainApp()
{
	m_hDC = GetDC(g_hEditorWnd);

	GET_SINGLE(CLineMgr)->Initialize();

	CLineMgr::GetInstance()->Initialize();

	return S_OK;
}

int CMainEditorApp::Update_MainApp(const float& fTimeDelta)
{
	CLineMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();

	return 0;
}

void CMainEditorApp::LateUpdate_MainApp(const float& fTimeDelta)
{
	CScrollMgr::GetInstance()->Scroll_Lock(1920.f, 1150.f);
	CKeyMgr::GetInstance()->LateUpdate();
	CLineMgr::GetInstance()->LateUpdate();
}
void CMainEditorApp::Render_MainApp()
{

	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	int iScrollX = (int)CScrollMgr::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->Get_ScrollY();


	CLineMgr::GetInstance()->Render(m_hDC);

}

CMainEditorApp* CMainEditorApp::Create()
{
	CMainEditorApp* pMainEditorApp = new CMainEditorApp;

	if (FAILED(pMainEditorApp->Ready_MainApp()))
	{
		delete pMainEditorApp;
		pMainEditorApp = nullptr;
	}

	return pMainEditorApp;
}
void CMainEditorApp::Free()
{
}
