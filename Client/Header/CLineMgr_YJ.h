#pragma once
enum class EDITTYPE
{
	LINE,
	OBSTACLE
};


class CLine;

class CLineMgr_YJ
{
	DECLARE_SINGLE(CLineMgr_YJ)

public:
	void	Initialize();
	void	Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();
public:
	void	Save_Data();
	void	Load_Data();

private:
	void	Key_Input();
	D3DXVECTOR3 GetObjectCenter(const vector<D3DXVECTOR3>& points);
	D3DXVECTOR3 GetPolygonCentroid(const vector<D3DXVECTOR3>& points);
private:
	//선 관리용
	list<CLine*>	m_Linelist;
	list<DATA>		m_ObjList;
	vector<D3DXVECTOR3> m_vecPoint;

	EDITTYPE m_eType;
};

