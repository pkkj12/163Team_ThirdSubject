#pragma once


class CObjYJ;

class CVampSurvival
{
public:
	explicit CVampSurvival();
	virtual ~CVampSurvival();

public:
	void Initialize()		;
	void Update()			;
	void LateUpdate()		;
	void Render(HDC hMemDC)	;
	void Release()			;

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

private:
	void Key_Input(); // 게임이 끝났을 때 스페이스 바를 입력하면 다음 씬으로 넘어가는 기능
};

