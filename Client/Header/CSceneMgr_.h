#pragma once
#include "Engine_Define.h"
#include "CScene.h"

enum SceneType_
{
	SM,
	JW,
	YJ,
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
	void ChangeScene(SceneType_ eSceneType);

private:
	CScene* m_pCurScene = nullptr;
};

