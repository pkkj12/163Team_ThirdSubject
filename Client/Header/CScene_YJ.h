#pragma once
class CScene_YJ
{
public:
	explicit CScene_YJ() {};
	virtual ~CScene_YJ() {};

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hMemDC) PURE;
	virtual void Release() PURE;
};

