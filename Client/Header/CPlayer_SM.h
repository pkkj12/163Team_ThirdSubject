#pragma once
#include "CObj_SM.h"
#include "Engine_Define.h"

class CPlayer_SM : public CObj_SM
{
public:
	CPlayer_SM();
	virtual ~CPlayer_SM();

public:
	void Initialize()		override;
	int Update()			override;
	void Late_Update()		override;
	void Render(HDC hDC)	override;
	void Release()			override;

private:
	void Key_Input_SM();

	vector<_vec3*> vecOriginPlayerVertex;
	vector<_vec3*> vecTransformPlayerVertex;
};

