#include "pch.h"
#include "CDoor.h"

CDoor::CDoor()
	: m_bIsDoorEnter(false)
{
	AddComponent(new CCollider);
}

CDoor::~CDoor()
{
}

void CDoor::update()
{
}

void CDoor::render(HDC _dc)
{
	render_component(_dc);
}

void CDoor::SetScale(Vec2 _scale)
{
	CObj::SetScale(_scale);
	GetCollider()->SetScale(_scale);
}

void CDoor::OnCollisionEnter(CObj* _pOtherObj)
{
	m_bIsDoorEnter = true;
}

void CDoor::OnCollisionExit(CObj* _pOtherObj)
{
	m_bIsDoorEnter = false;
}

