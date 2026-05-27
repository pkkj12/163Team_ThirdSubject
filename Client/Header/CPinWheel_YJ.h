#pragma once

#include "CBullet_YJ.h"
class CPinWheel_YJ
	: public CBullet_YJ
{

public:
	explicit CPinWheel_YJ();
	virtual ~CPinWheel_YJ();

public:
	virtual HRESULT Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Free() override;


public:
	virtual void SetCollide(CObjYJ* pObj) override;
};

