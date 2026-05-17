#include "pch.h"
#include "CSceneMgr_.h"

#include "CScene_JW.h"

IMPLEMENT_SINGLETON(CSceneMgr_)

CSceneMgr_::CSceneMgr_()
{
}

CSceneMgr_::~CSceneMgr_()
{
	Release();
}

void CSceneMgr_::Initialize()
{
	ChangeScene(SceneType_::JW);
}

int CSceneMgr_::Update()
{
	if (!m_pCurScene)
		return 0;

	if (m_pCurScene->Update() == 1)
	{
		// ¾À Á¦°Å Ã³¸®?
		Safe_Delete<CScene*>(m_pCurScene);
	}
}

void CSceneMgr_::LateUpdate()
{
	m_pCurScene->LateUpdate();
}

void CSceneMgr_::Render(HDC hDC)
{
	m_pCurScene->Render(hDC);
}

void CSceneMgr_::Release()
{
	Safe_Delete<CScene*>(m_pCurScene);
}

void CSceneMgr_::ChangeScene(SceneType_ eSceneType)
{
	Safe_Delete<CScene*>(m_pCurScene);

	switch (eSceneType)
	{
	case SceneType_::JW:
		m_pCurScene = new CScene_JW;
	}

	m_pCurScene->Initialize();
}
