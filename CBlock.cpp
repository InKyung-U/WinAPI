#include "pch.h"
#include "CBlock.h"

#include "CCollider.h"
#include "CMovement.h"

CBlock::CBlock()
{
	AddComponent(new CCollider);
}

CBlock::~CBlock()
{
}

void CBlock::update()
{
}

void CBlock::render(HDC _dc)
{
	render_component(_dc);
}

void CBlock::SetScale(Vec2 _scale)
{
	CObj::SetScale(_scale);
	GetCollider()->SetScale(_scale);
}

void CBlock::OnCollisionEnter(CObj* _pOtherObj)
{
	if (_pOtherObj->GetMovement())
	{
		_pOtherObj->GetMovement()->OnGround();
	}
}

void CBlock::OnCollisionExit(CObj* _pOtherObj)
{
	if (_pOtherObj->GetMovement())
	{
		_pOtherObj->GetMovement()->OnAir();
	}
}
