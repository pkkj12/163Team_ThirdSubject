#pragma once

#include "CBase.h"
class CLine_YJ;
class CObjYJ abstract
	: public CBase
{
public:
	explicit CObjYJ();
	virtual ~CObjYJ();
public:
	virtual HRESULT Ready()			PURE;
	virtual int Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Free()				PURE;


	virtual void AddLine(CLine_YJ* tLine) {}
	void	AddVertex(_vec3 vVertex) { m_vecVertex.push_back(&vVertex); }
	void	AddOriginVertex(const D3DXVECTOR3& v) {
		m_vecOriginVertex.push_back(new D3DXVECTOR3(v));
		m_vecVertex.push_back(new D3DXVECTOR3);
	}
public:
	const VECYJINFO& GetInfo() { return m_tInfo; }
	const _vec3& GetAngle() { return m_vWorldAngle; }

	void	AddPos(const _vec3& v) { m_tInfo.vPos += v; }
	void	SetPos(_vec3 vCenter) { m_tInfo.vPos = vCenter;}
	_vec3   GetPos() const { return m_tInfo.vPos;}
	void	SetType(YJUTIL::OBJ_TYPE eType) { m_eType = eType; }
	void	SetDir(D3DXVECTOR3 vDir) { m_tInfo.vDir = vDir; }
	void	SetAngle(float fAngle) { m_vWorldAngle.z = fAngle; }
	YJUTIL::OBJ_TYPE	GetType() const { return m_eType;}
public:
	const VECYJINFO& GetTransform() const { return m_tInfo; }
	//const vector<POINT>& GetVecDrawPoints() {return m_ptDraw;}
	const vector<D3DXVECTOR3*>& GetVecWorldVertexs() const { return m_vecVertex; }

	void MakeWorldMatrix();
	void UpdateWorldVertex();

public:
	void SetCollide(bool b) { m_bIsCollide = b; }
	virtual void SetCollide(CObjYJ* pObj) {};
	const bool GetCollide() { return m_bIsCollide; }

protected:
	VECYJINFO m_tInfo;
	vector<_vec3*> m_vecOriginVertex;
	vector<_vec3*> m_vecVertex;

	bool m_bIsCollide;

	_vec3			m_vWorldScale = { 1.f, 1.f, 1.f };
	_vec3			m_vWorldAngle = { 0.f, 0.f, 0.f };
	const _vec3	m_vWorldTrans = { 400.f, 300.f, 0.f };
	float	m_fSpeed;
	float   m_fDistance;
	YJUTIL::OBJ_TYPE m_eType;
};

