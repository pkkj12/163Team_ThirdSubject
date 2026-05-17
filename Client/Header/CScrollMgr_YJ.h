#pragma once
class CScrollMgr_YJ
{
	DECLARE_SINGLE(CScrollMgr_YJ)

public:
	float		Get_ScrollX() { return m_fScrollX; }
	float		Get_ScrollY() { return m_fScrollY; }

public:
	void		Set_ScrollX(float fX) { m_fScrollX += fX; }
	void		Set_ScrollY(float fY) { m_fScrollY += fY; }
	void	    Scroll_Lock(float fX, float fY);
	bool		IsLockX() const { return m_bLockX; }
	bool		IsLockY() const { return m_bLockY; }
private:
	float				m_fScrollX;
	float				m_fScrollY;

	bool		m_bLockX = false;
	bool		m_bLockY = false;
};

