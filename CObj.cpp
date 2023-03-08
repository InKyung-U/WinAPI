#include "pch.h"
#include "CObj.h"

#include "CComponent.h"

CObj::CObj()
	: m_bDead(false)
	, m_arrCom{}
{
}

CObj::CObj(const CObj& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_arrCom{}
	, m_bDead(false)
{
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr != _origin.m_arrCom[i])
		{			
			AddComponent(_origin.m_arrCom[i]->Clone());
		}
	}
}


CObj::~CObj()
{
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			delete m_arrCom[i];
		}
	}
}

void CObj::finalupdate()
{
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->update();
	}
}

void CObj::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc
		, int(vRenderPos.x - (m_vScale.x / 2.f))
		, int(vRenderPos.y - (m_vScale.y / 2.f))
		, int(vRenderPos.x + (m_vScale.x / 2.f))
		, int(vRenderPos.y + (m_vScale.y / 2.f)));
}

void CObj::render_component(HDC _dc)
{
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->render(_dc);
	}
}

void CObj::AddComponent(CComponent* _pCom)
{
	ECOM_TYPE eType = _pCom->GetType();
	m_arrCom[(UINT)eType] = _pCom;
	_pCom->m_pOwner = this;

	if (false == _pCom->CheckOwner())
	{
		assert(nullptr);
	}
}