#pragma once
#include "Engine_Define.h"
#include "CObj_SM.h"

class CMonster_SM : public CObj_SM
{
public:
	CMonster_SM();
	~CMonster_SM();

public:
	void Initialize()		override;
	int	Update()			override;
	void Late_Update()		override;
	void Render(HDC hDC)	override;
	void Release()			override;

private:
	vector<_vec3*> vecOriginPlayerVertex;
	vector<_vec3*> vecTransformPlayerVertex;

};

