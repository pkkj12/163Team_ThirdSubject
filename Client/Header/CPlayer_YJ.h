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

	virtual void SetCollide(CObjYJ* pObj) override;

	void OffSet();
	void SetHP(int iAtk) { m_iLife -= iAtk; }
	bool IsDead() const { return m_bDead; }
	bool IsGod() const { return m_bGod; }
	void SetGod(bool bGod) { m_bGod = bGod; }
	int GetHp() const { return m_iLife; }
private:
	void Key_Input();
private:
	_vec3 m_vecOriginalPosin;
	_vec3 m_vecPosin;

	CObjYJ* m_pShield;
	int	  m_iLife;
	bool  m_bDead;
	float m_fDistance;
	float m_fGodTime;
	bool m_bGod;

	float m_fFadeTime;
};

