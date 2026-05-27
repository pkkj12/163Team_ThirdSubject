#pragma once
#include "Engine_Define.h"
#include "CScene.h"

enum SceneType_
{
	YJ,
	JW,
	SM,
	YB,

	SCENE_END
};

class CSceneMgr_
{
private:
	CSceneMgr_();
	~CSceneMgr_();

private:
	DECLARE_SINGLETON(CSceneMgr_)

public:
	void Initialize();
	int	 Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void ChangeScene(SceneType_ eSceneType = SceneType_::SCENE_END);

private:
	void KeyInput();

private:
	pair<SceneType_, CScene*> m_pCurScene = { SceneType_::SCENE_END, nullptr };
};