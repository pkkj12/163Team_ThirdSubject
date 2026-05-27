#pragma once

#include "CObjYJ.h"
class CMonster_YJ
	: public CObjYJ
{

public:
	explicit CMonster_YJ();
	virtual ~CMonster_YJ();
public:
	virtual HRESULT Ready()			PURE;
	virtual int Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Free()				PURE;
};

