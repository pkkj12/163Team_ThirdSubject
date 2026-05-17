#pragma once

#include "CScene_YJ.h"

class CObjYJ;
class CVampSurvival
	:public CScene_YJ
{
public:
	explicit CVampSurvival();
	virtual ~CVampSurvival();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hMemDC) override;
	void Release() override;

private:
	CObjYJ* m_pPlayer;
	vector<DATA> m_tObstacles;
};

