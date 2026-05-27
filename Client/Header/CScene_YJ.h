#pragma once
#include "CScene.h"

class CVampSurvival;

class CScene_YJ
	: public CScene
{
public:
	explicit CScene_YJ() {};
	virtual ~CScene_YJ()
	{
		Release();
	};

public:
	virtual void Initialize()		 override;
	virtual int Update()			 override;
	virtual void LateUpdate()		 override;
	virtual void Render(HDC hMemDC)	 override;
	virtual void Release()			 override;

private:
	CVampSurvival* m_pVS = nullptr;
};

