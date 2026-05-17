#include "pch.h"
#include "CObj_JW.h"

CObj_JW::CObj_JW()
{
	m_vecLocalVertex.reserve(3);
	m_vecLocalVertex.reserve(3);
}

CObj_JW::~CObj_JW()
{
	Free();
}

void CObj_JW::Initialize_WorldVertex()
{
	for_each(m_vecWorldVertex.begin(), m_vecWorldVertex.end(), [](_vec3*& pV)
		{
			Safe_Delete<_vec3*>(pV);
		});
	m_vecWorldVertex.clear();

	for (int i = 0; i < m_vecLocalVertex.size(); ++i)
		m_vecWorldVertex.push_back(new _vec3);
}

void CObj_JW::Free()
{
	for_each(m_vecLocalVertex.begin(), m_vecLocalVertex.end(), [](_vec3*& pV)
		{
			Safe_Delete<_vec3*>(pV);
		});
	m_vecLocalVertex.clear();

	for_each(m_vecWorldVertex.begin(), m_vecWorldVertex.end(), [](_vec3*& pV)
		{
			Safe_Delete<_vec3*>(pV);
		});
	m_vecWorldVertex.clear();
}