#include "pch.h"
#include "CTable.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CStageMgr.h"


CTable::CTable()
	: m_pTex()
	, m_bTableMove(false)
	, m_bMovingTable(false)
	, m_fTableSec(0.f)
	, m_vTableMoveScale{}
{
	AddComponent(new CCollider);
}

CTable::~CTable()
{
}

void CTable::update()
{
	if (m_bMovingTable)
	{
		m_fTableSec += DS;
		if (m_fTableSec < 1.f)
		{
			AddPos(m_vTableMoveScale);
			CStageMgr::GetInst()->SetTablePos(GetPos());
		}
		else
		{
			m_bMovingTable = false;
			m_fTableSec = 0.f;
		}
	}
}

void CTable::render(HDC _dc)
{
	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, vRenderPos.x - iWidth / 2
		, vRenderPos.y - iHeight / 2
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));

	render_component(_dc);
}

void CTable::SetScale(Vec2 _scale)
{
	CObj::SetScale(_scale);
	GetCollider()->SetScale(_scale);
}

void CTable::OnCollisionEnter(CObj* _pOtherObj)
{
	m_bTableMove = true;
}

void CTable::OnCollisionExit(CObj* _pOtherObj)
{
	m_bTableMove = false;
}
