#include "pch.h"
#include "CCollider.h"

#include "CObj.h"
#include "CCore.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: CComponent(ECOM_TYPE::COLIIDER)
	, m_iColID(g_iNextID++)
	, m_iCollisionCount(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: CComponent(_origin)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_vFinalPos(_origin.m_vFinalPos)
	, m_iColID(g_iNextID++)
	, m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::update()
{
	// 충돌체의 이번 프레임의 최종 위치	
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	HPEN hPen = nullptr;

	if (m_iCollisionCount > 0)
	{
		hPen = CCore::GetInst()->GetRedPen();
	}
	else if(m_iCollisionCount == 0)
	{
		hPen = CCore::GetInst()->GetGreenPen();
	}		
	else
	{
		assert(nullptr);
	}	

	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc
		, int(vRenderPos.x - m_vScale.x / 2.f)
		, int(vRenderPos.y - m_vScale.y / 2.f)
		, int(vRenderPos.x + m_vScale.x / 2.f)
		, int(vRenderPos.y + m_vScale.y / 2.f));

	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);
}

// 충돌 알림
void CCollider::OnCollisionEnter(CCollider* _pCollider)
{
	++m_iCollisionCount;
	GetOwner()->OnCollisionEnter(_pCollider->GetOwner());
}

void CCollider::OnCollision(CCollider* _pCollider)
{
	GetOwner()->OnCollision(_pCollider->GetOwner());
}

void CCollider::OnCollisionExit(CCollider* _pCollider)
{
	--m_iCollisionCount;
	GetOwner()->OnCollisionExit(_pCollider->GetOwner());
}