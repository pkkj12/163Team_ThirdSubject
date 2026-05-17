#pragma once
#include "Engine_Define.h"

class CCollisionMgr_SM
{
private:
	CCollisionMgr_SM();
	CCollisionMgr_SM(const CCollisionMgr_SM &rhs) = delete;
	CCollisionMgr_SM& operator=(const CCollisionMgr_SM rCCollisionMgr_SM) = delete;
	~CCollisionMgr_SM();

public:
	void Collision_AABB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex);
	void Collision_OBB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex);

	bool Check_AABB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex);
	bool Check_OBB_SM(vector<_vec3> vecDstVertex, vector<_vec3> vecSrcVertex);
	
public:
	static CCollisionMgr_SM* Get_Instnace()
	{
		if (!m_pInstance_SM)
		{
			m_pInstance_SM = new CCollisionMgr_SM;
		}

		return m_pInstance_SM;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance_SM)
		{
			delete m_pInstance_SM;
			m_pInstance_SM = nullptr;
		}
	}

private:
	static CCollisionMgr_SM* m_pInstance_SM;
	
	
};

