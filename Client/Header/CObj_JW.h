#pragma once
#include "CBase.h"
#include "Define_JW.h"

class CObj_JW abstract
	//: public CBase
{
public:
	explicit CObj_JW();
	virtual	 ~CObj_JW();

public:
	virtual void Initialize()		PURE;
	virtual int	 Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC hDC)	PURE;

public:
	const INFO_JW&	GetInfo_JW()		const { return m_tWorldInfo; }
	const _vec3&	GetPosVec3_JW()		const { return m_tWorldInfo.vPos; }
	const _vec3&	GetRotVec3_JW()		const { return m_tWorldInfo.vRotate; }
	const _vec3&	GetScaleVec3_JW()	const { return m_tWorldInfo.vScale; }
	const vector<_vec3*>& const GetWorldVertex() const { return m_vecWorldVertex; }
	virtual const _uint&& const GetIDX() const { return -1; }
	virtual const _float&& const GetDistance() const { return 0.f; }

protected:
	void Initialize_WorldVertex();
protected:
	INFO_JW m_tLocalInfo;
	INFO_JW m_tWorldInfo;

	vector<_vec3*> m_vecLocalVertex;
	vector<_vec3*> m_vecWorldVertex;

private:
	virtual void Free();

public:
	const CObj_JW* const GetParent_JW() const { return m_pParent; }
	const CObj_JW* const GetChild_JW() const { return m_pChild; }
	void SetParent_JW(CObj_JW* pParent)
	{
		if (m_pParent)
			return;

		m_pParent = pParent;
//		m_pParent->AddRef();

		m_pParent->SetChild_JW(this);
	}
	void SetChild_JW(CObj_JW* pChild)
	{
		if (m_pChild)
			return;

		m_pChild = pChild;
//		m_pChild->AddRef();

		m_pChild->SetParent_JW(this);
	}
public:
	void OnCollisionStay(bool bIsCollided) 
	{
		m_bIsCollided = bIsCollided;
	};
protected:
	bool m_bIsCollided = false;

protected:
	CObj_JW* m_pParent	= nullptr;
	CObj_JW* m_pChild	= nullptr; // 원래는 자식은 여러 명이 갖고 있어야 하는데, 지금 구조를 생각하지는 않겠음...
	bool	 m_bDestory = false;
};

