#pragma once

#include "CMonster_YJ.h"

#define SIZE_OCTAGON 40.f

enum class BOSSSTATE
{
	MOVE,
	ATTACK,
	STOP
};


enum class BOSSSKILL
{
	BASIC,
	EIGHTDIR,
	BOMB,
	END
};

class CBoss_YJ
	: public CMonster_YJ 
{
public:
	explicit CBoss_YJ();
	virtual ~CBoss_YJ();
public:
	virtual HRESULT Ready()			override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Free()				override;

protected:
	void	Update_Move();
	void	Update_Attack();
	//void	Update_Bomb();
	//void	Update_EightDir();
protected:
	void	Basic();
	void	EightDir();
	void	Bomb();

private:

	HBRUSH		m_hRedBrush;

	BOSSSTATE	m_eState;
	BOSSSKILL	m_eSkillState;
	float		m_fTimeDelta;
	float		m_fShootTick;
};

