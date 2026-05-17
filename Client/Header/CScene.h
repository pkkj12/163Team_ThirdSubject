#pragma once

typedef HDC;

class CScene
{
public:
	virtual ~CScene() {}

	virtual void Initialize()		PURE;
	virtual int	 Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;
};

