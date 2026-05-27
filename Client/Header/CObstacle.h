#pragma once

#include "CObjYJ.h"

class CLine_YJ;
class CObstacle
	: public CObjYJ
{

public:
	explicit CObstacle();
	virtual ~CObstacle();

public:
	virtual HRESULT Ready()	 override;
	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Free() override;
	virtual void AddLine(CLine_YJ* tLine)
	{
		m_vecLines.push_back(tLine);
	}
private:
	vector<CLine_YJ*> m_vecLines;
};

