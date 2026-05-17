#pragma once
#include "Define_SM.h"

class CObj_SM
{
public:
	CObj_SM();
	virtual ~CObj_SM();


public:
	virtual void Initialize() PURE_SM;
	virtual int Update() PURE_SM;
	virtual void Late_Update() PURE_SM;
	virtual void Render(HDC hDC) PURE_SM;
	virtual void Release() PURE_SM;

protected:
	INFO_SM		m_tInfo_SM;

	bool		m_bDead_SM;
	float		m_fSpeed_SM;

	float		m_fAngle_SM;
};

