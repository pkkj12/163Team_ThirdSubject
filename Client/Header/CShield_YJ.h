#pragma once

#include "CObjYJ.h"

#define SHIELD_RADIUS 16.f
class CObj;
class CShield_YJ
	: public CObjYJ
{
public:
	explicit CShield_YJ();
	virtual ~CShield_YJ();
public:
	virtual HRESULT Ready()			override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Free()				override;
public:
	void RotateAroundPlayer();
	void SetOwner(CObjYJ* pOwner) { m_pOwner = pOwner; }
private:
	CObjYJ* m_pOwner = nullptr;
	float	m_fRadius = 50.f; // 플레이어와 쉴드 간의 거리 
	float	m_fAngle = 0.f;		// 각도
	float	m_fRotSpeed = 3.f; // 쉴드의 회전 속도
};

