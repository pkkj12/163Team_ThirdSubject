#pragma once
class CScrollMgr
{

	DECLARE_SINGLE(CScrollMgr)

public:
	float		Get_ScrollX() { return m_fScrollX; }
	float		Get_ScrollY() { return m_fScrollY; }

public:
	void		Set_ScrollX(float fX) { m_fScrollX += fX; }
	void		Set_ScrollY(float fY) { m_fScrollY += fY; }
	void	    Scroll_Lock(float fX, float fY);

private:
	float				m_fScrollX;
	float				m_fScrollY;
};

