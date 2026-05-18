#include "pch.h"
#include "CBoss_YJ.h"
#include "CScrollMgr_YJ.h"
#include "CTimeMgr_YJ.h"
#include "CObjMgr_YJ.h"
#include "CBullet_YJ.h"
#include "CPinWheel_YJ.h"

CBoss_YJ::CBoss_YJ() : m_eState(BOSSSTATE::STOP), m_fTimeDelta(0.f), m_eSkillState(BOSSSKILL::END)
, m_fShootTick(0.f)
{
}

CBoss_YJ::~CBoss_YJ()
{
	Free();
}

HRESULT CBoss_YJ::Ready()
{
	m_tInfo.vPos = { 600.f, 500.f ,0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };

	m_vecOriginVertex.push_back(new _vec3(SIZE_OCTAGON, -SIZE_OCTAGON, 0.f));
	m_vecOriginVertex.push_back(new _vec3(SIZE_OCTAGON, SIZE_OCTAGON, 0.f));
	m_vecOriginVertex.push_back(new _vec3(SIZE_OCTAGON * 0.75, SIZE_OCTAGON * 1.25, 0.f));
	m_vecOriginVertex.push_back(new _vec3(-SIZE_OCTAGON * 0.75, SIZE_OCTAGON * 1.25, 0.f));
	m_vecOriginVertex.push_back(new _vec3(-SIZE_OCTAGON, SIZE_OCTAGON, 0.f));
	m_vecOriginVertex.push_back(new _vec3(-SIZE_OCTAGON, -SIZE_OCTAGON, 0.f));
	m_vecOriginVertex.push_back(new _vec3(-SIZE_OCTAGON * 0.75, -SIZE_OCTAGON * 1.25, 0.f));
	m_vecOriginVertex.push_back(new _vec3(SIZE_OCTAGON * 0.75, -SIZE_OCTAGON * 1.25, 0.f));

	for(int i = 0; i < m_vecOriginVertex.size(); ++i)
	{
		m_vecVertex.push_back(new D3DXVECTOR3);
	}


	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));

	return S_OK;
}

int CBoss_YJ::Update()
{
	m_fTimeDelta += fDT;

	__super::MakeWorldMatrix();
	__super::UpdateWorldVertex();

	switch (m_eState)
	{
	case BOSSSTATE::STOP:
		if (m_fTimeDelta > 2.f)
		{
			m_eState = BOSSSTATE::MOVE;
			m_fTimeDelta = 0.f;
		}
		break;
	case BOSSSTATE::MOVE:
		if (m_fTimeDelta > 3.f)
		{
			m_eState = BOSSSTATE::ATTACK;
			//int iRand = rand() % 2;
			int iRand = 1;
			m_eSkillState = (BOSSSKILL)iRand;
			m_fTimeDelta = 0.f;
		}
		else
			Update_Move();
		break;
	case BOSSSTATE::ATTACK:
		if (m_fTimeDelta > 5.f)
		{
			m_eState = BOSSSTATE::STOP;
			m_fTimeDelta = 0.f;
		}
		else
			Update_Attack();
		break;
	}
	return OBJ_NOEVENT;
}

void CBoss_YJ::LateUpdate()
{
}

void CBoss_YJ::Render(HDC hDC)
{
	float m_fScrollX = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollX();
	float m_fScrollY = GET_SINGLE(CScrollMgr_YJ)->Get_ScrollY();
	MoveToEx(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY, nullptr);
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		LineTo(hDC, m_vecVertex[i]->x - m_fScrollX, m_vecVertex[i]->y - m_fScrollY);
	}
	LineTo(hDC, m_vecVertex[0]->x - m_fScrollX, m_vecVertex[0]->y - m_fScrollY);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, m_hRedBrush);

	POINT pts[8];
	ZeroMemory(&pts, sizeof(POINT) * 8);
	int iIdx = 0;
	for (auto& p : m_vecVertex)
	{
		pts[iIdx].x = (int)p->x - m_fScrollX;
		pts[iIdx].y = (int)p->y - m_fScrollY;
		iIdx++;
	}
	Polygon(hDC, pts, 8);
	SelectObject(hDC, hOldBrush);
}

void CBoss_YJ::Free()
{
	DeleteObject(m_hRedBrush);
}

void CBoss_YJ::Update_Move()
{
	CObjYJ* pPlayer = GET_SINGLE(CObjMgr_YJ)->GetPlayer();
	D3DXVECTOR3 vDir = pPlayer->GetPos() - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_tInfo.vPos += 2.f * vDir;
}

void CBoss_YJ::Update_Attack()
{
	m_fShootTick += fDT;
	if (m_fShootTick > 1 && m_eSkillState < BOSSSKILL::END)
	{
		m_fShootTick = 0;
		switch (m_eSkillState)
		{
		case BOSSSKILL::BASIC:
			Basic();
			break;
		case BOSSSKILL::EIGHTDIR:
			EightDir();
			break;
		case BOSSSKILL::BOMB:
			Bomb();
			break;
		}
	}
}

void CBoss_YJ::Basic()
{
	CObjYJ* pPlayer = GET_SINGLE(CObjMgr_YJ)->GetPlayer();
	D3DXVECTOR3 vDir = pPlayer->GetPos() - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	// ÃÑ¾Ë »ý¼º
	CBullet_YJ* pBullet = new CBullet_YJ;
	pBullet->Ready();
	pBullet->SetDir(vDir);
	pBullet->SetPos(m_tInfo.vPos);
	pBullet->SetType(OBJ_MBULLET);
	GET_SINGLE(CObjMgr_YJ)->AddObject(OBJ_MBULLET, pBullet);

}

void CBoss_YJ::EightDir()
{
	D3DXVECTOR3 vBossPos = m_tInfo.vPos;
	float space = 40.f;

	for (int i = 0; i < 30; i++)
	{
		D3DXMATRIX	matRotZ;


		float fAngle = D3DXToRadian(225.f + 20.f * (i + 1));

		D3DXMatrixRotationZ(&matRotZ, fAngle);
		D3DXVECTOR3 vArrangeDir(1.f, 0.f, 0.f);
		D3DXVec3TransformNormal(&vArrangeDir, &vArrangeDir, &matRotZ);
		D3DXVec3Normalize(&vArrangeDir, &vArrangeDir);
			//Vec2 arrangeDir = Utils::GetDirection(225.f + 20.f * (i + 1));
			//arrangeDir.Normalize();
		CPinWheel_YJ* pBullet = new CPinWheel_YJ;
		pBullet->Ready();
		pBullet->SetPos(vBossPos);
		pBullet->SetAngle(-i * 12.f);
		pBullet->SetDir(vArrangeDir);
		pBullet->SetType(OBJ_MBULLET);
		GET_SINGLE(CObjMgr_YJ)->AddObject(OBJ_MBULLET, pBullet);
		//bullet->SetSpeed(200.f);
		//bullet->Set_InitPos(bossPos);
	}
}

void CBoss_YJ::Bomb()
{
}

//void CBoss_YJ::Update_Skill()
//{
//}
