#include "pch.h"
#include "CGate.h"

CGate::CGate()
	: m_bTouchGate(false)
{
	AddComponent(new CCollider);
}

CGate::~CGate()
{
}

void CGate::update()
{
}

void CGate::render(HDC _dc)
{
	render_component(_dc);

}

void CGate::SetScale(Vec2 _scale)
{
	CObj::SetScale(_scale);
	GetCollider()->SetScale(_scale);
}

void CGate::OnCollisionEnter(CObj* _pOtherObj)
{
	m_bTouchGate = true;
}