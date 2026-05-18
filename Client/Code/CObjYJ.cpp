#include "pch.h"
#include "CObjYJ.h"



CObjYJ::CObjYJ() : m_fSpeed(0.f), m_fDistance(0.f), m_bIsCollide(false)
{
	ZeroMemory(&m_tInfo, sizeof(VECYJINFO));
	//ZeroMemory(&m_tOriginInfo, sizeof(VECYJINFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	//D3DXMatrixIdentity(&m_tOriginInfo.matWorld);
}

CObjYJ::~CObjYJ()
{
}


void CObjYJ::MakeWorldMatrix()
{
    D3DXMATRIX	matScale, matTrans;
    D3DXMATRIX	matRot;

    // 회전 행렬
    //D3DXMatrixIdentity(&matRotZ); //포신만 돌아가게끔 하려고 단 사각형이 회전하지 않음 => 포신만 돌아가게하려면 포신 각도를 따로 두어야할까?
    //D3DXMatrixRotationZ(&matRotZ, m_vWorldAngle.z);
    D3DXMatrixRotationYawPitchRoll(&matRot, m_vWorldAngle.x, m_vWorldAngle.y, m_vWorldAngle.z);

    // 크기 행렬
    D3DXMatrixScaling(&matScale, m_vWorldScale.x, m_vWorldScale.y, m_vWorldScale.z);

    // 이동 행렬
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRot * matTrans;


}

void CObjYJ::UpdateWorldVertex()
{
    //m_ptDraw.clear();
    //m_ptDraw.reserve(m_vVertex.size());

    //for (auto& v : m_vVertex) {
    //    D3DXVECTOR3 vOut; //월드 좌표
    //    D3DXVec3TransformCoord(&vOut, &v, &m_tTransform.matWorld); //정점 위치 업데이트
    //    POINT pt = { (long)vOut.x, (long)vOut.y };
    //    m_ptDraw.push_back(pt);
    //}

    if (m_vecVertex.size() != m_vecOriginVertex.size())
        m_vecVertex.resize(m_vecOriginVertex.size());

    for (size_t i = 0; i < m_vecOriginVertex.size(); ++i) {
        D3DXVec3TransformCoord(m_vecVertex[i], m_vecOriginVertex[i], &m_tInfo.matWorld);
    }


}