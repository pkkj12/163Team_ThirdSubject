#pragma once

#include "CObjYJ.h"

#define SIZE_RECTANGLE 20.f
#define DISTANCE	10.f
class CPlayer_YJ
	: public CObjYJ
{

public:
	explicit CPlayer_YJ();
	virtual ~CPlayer_YJ();

public:
	virtual HRESULT Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Free() override;

	void OffSet();
private:
	void Key_Input();
private:
	_vec3 m_vecOriginalPosin;
	_vec3 m_vecPosin;

	CObjYJ* m_pShield;
	float m_fDistance;
};

