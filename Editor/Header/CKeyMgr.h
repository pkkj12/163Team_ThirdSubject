#pragma once
class CKeyMgr
{

	DECLARE_SINGLE(CKeyMgr)
public:
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	bool Key_Pressing(int iKey);
	bool Key_Down(int iKey);
	bool Key_Up(int iKey);

private:
	bool m_bKeyState[0xff];
};

