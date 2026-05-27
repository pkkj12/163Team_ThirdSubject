#pragma once
class CLine
{
public:
	CLine();
	CLine(D3DXVECTOR3& tLeft, D3DXVECTOR3& tRight);
	~CLine();

public:
	void Render(HDC hDC);

public:
	const LINE* Get_Line() const { return &m_tLine; }

private:
	LINE	m_tLine;
};

