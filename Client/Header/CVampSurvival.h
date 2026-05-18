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
	bool IsEndGame();

private:
	CObjYJ* m_pPlayer;
	vector<DATA> m_tObstacles;
	float		m_fTime;
	bool		m_bIsEnd;


	TCHAR		m_szSec[16];
	RECT		m_rectHp = { 20, 20, 220, 70 };
	RECT		m_rectTime = { WINCX / 2 - 300, 20, WINCX / 2 + 300, 70 };
	RECT		m_rectEnd = { WINCX / 2 - 300, 200, WINCX / 2 + 300, 400 };
};

