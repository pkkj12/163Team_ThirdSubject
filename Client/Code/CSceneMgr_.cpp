#include "pch.h"
#include "CSceneMgr_.h"

#include "CScene_JW.h"
#include "CScene_YJ.h"

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
	ChangeScene(SceneType_::YJ);
}

int CSceneMgr_::Update()
{
	if (!m_pCurScene.second)
		return 0;

	if (m_pCurScene.second->Update() == 1)
	{
		// ¾À Á¦°Å Ã³¸®?
		Engine::Safe_Delete<CScene*>(m_pCurScene.second);
		m_pCurScene.first = SceneType_::SCENE_END;
	}
}

void CSceneMgr_::LateUpdate()
{
	m_pCurScene.second->LateUpdate();
}

void CSceneMgr_::Render(HDC hDC)
{
	m_pCurScene.second->Render(hDC);

	KeyInput();
}

void CSceneMgr_::Release()
{
	Engine::Safe_Delete<CScene*>(m_pCurScene.second);
}

void CSceneMgr_::ChangeScene(SceneType_ eSceneType)
{
	if (m_pCurScene.first == eSceneType)
		return;

	Engine::Safe_Delete<CScene*>(m_pCurScene.second);

	switch (eSceneType)
	{
	case SceneType_::JW:
		m_pCurScene.second = new CScene_JW;
		break;
	case SceneType_::YJ:
		m_pCurScene.second = new CScene_YJ;
		break;
	default:
		(*(_int*)(&m_pCurScene.first)) = 0;
		return;
	}

	m_pCurScene.first = eSceneType;
	m_pCurScene.second->Initialize();
}

void CSceneMgr_::KeyInput()
{
	if (GetAsyncKeyState(VK_F1))
		ChangeScene(SceneType_::YJ);
	if (GetAsyncKeyState(VK_F2))
		ChangeScene(SceneType_::JW);
	if (GetAsyncKeyState(VK_F3))
		ChangeScene
		(
			(SceneType_)
			((*(_int*)(&m_pCurScene.first)) + 1)
		);

}
