#pragma once
class CLine_YJ
{
public:
	CLine_YJ();
	CLine_YJ(D3DXVECTOR3& tLeft, D3DXVECTOR3& tRight);
	~CLine_YJ();

public:
	void Render(HDC hDC);

public:
	const LINE* Get_Line() const { return &m_tLine; }

private:
	LINE	m_tLine;
};

