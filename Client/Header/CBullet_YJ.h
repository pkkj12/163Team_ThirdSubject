#pragma once

#include "CObjYJ.h"

#define	BULLET_RADIUS 20.f

class CBullet_YJ
	: public CObjYJ
{
public:
	explicit CBullet_YJ();
	virtual ~CBullet_YJ();
public:
	virtual HRESULT Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Free() override;


public:
	float	GetRadius() const { return m_fRadius; }
private:
	float m_fRadius = BULLET_RADIUS;
};

