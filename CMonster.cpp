#include "pch.h"
#include "CMonster.h"

#include "CKeyMgr.h"
#include "CBullet.h"

#include "CFSM.h"
#include "CState_Idle.h"
#include "CState_Trace.h"
#include "CState_Attack.h"
#include "CState_Dead.h"

#include "CResMgr.h"
#include "CStageMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CStage.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CMonster::CMonster()
	: m_iHitCount(5)
{	
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	pCollider->SetScale(Vec2(80.f, 120.f));

	AddComponent(pCollider);

	// Animator 생성
	CTexture* pAnimAtlasTex = CResMgr::GetInst()->LoadTexture(L"RedMane", L"texture\\ib\\rm.bmp");
	pAnimator = new CAnimator;
	CAnimation* pAnim = nullptr;
	pAnimator->LoadAnimation(L"animation\\monster\\RMANE_WALK_L.anim");
	pAnimator->LoadAnimation(L"animation\\monster\\RMANE_WALK_UD.anim");
	pAnimator->LoadAnimation(L"animation\\monster\\RMANE_STAND_L.anim");
	pAnimator->LoadAnimation(L"animation\\monster\\RMANE_WALK_R.anim");

	AddComponent(pAnimator);
	m_sCurAnimationName = L"RMANE_WALK_L";
	m_sChangeAniName = m_sCurAnimationName;
	pAnimator->Play(m_sCurAnimationName);


	
	AddComponent(new CCollider);	
	AddComponent(new CFSM);

	GetFSM()->AddState(new CState_Idle);
	GetFSM()->AddState(new CState_Trace);
	GetFSM()->AddState(new CState_Attack);
	GetFSM()->AddState(new CState_Dead);

	GetFSM()->SetState(EMON_STATE::MON_IDLE);


	tMonInfo info = {};

	info.strMonName = L"Monster";
	info.m_fAtt = 20.f;
	info.m_fMaxHP = 200.f;
	info.m_fCurHP = 200.f;
	info.m_fDetectRange = 500.f;
	info.m_fAttRange = 100.f;
	info.m_fSpeed = 80.f;

	SetMonInfo(info);
}

CMonster::~CMonster()
{
	DeleteObject(this);
}

void CMonster::update()
{
	if (KTAP(KEY::NUM0))
	{
		DeleteObject(this);
	}

	if (m_sChangeAniName != m_sCurAnimationName)
	{
		m_sCurAnimationName = m_sChangeAniName;
		pAnimator->Play(m_sCurAnimationName);
	}

	if (m_iHitCount == 0)
	{
		DeleteObject(this);
	}
}

void CMonster::render(HDC _dc)
{
	CObj::render(_dc);

	render_component(_dc);
}

void CMonster::OnCollisionEnter(CObj* _pOtherObj)
{
	CBullet* pBullet = dynamic_cast<CBullet*>(_pOtherObj);

	if (nullptr != pBullet)
	{
		m_iHitCount -= 1;

		if (m_iHitCount <= 0)
		{
			DeleteObject(this);
		}		
	}

	CStageMgr::GetInst()->SubRoseCount();
	CSound* Hit = CResMgr::GetInst()->FindSound(L"PlayerHit");
	Hit->Play();
	CStageMgr::GetInst()->TurnOnPlayerHit();

}

bool CMonster::CanIMoveNextTile(Vec2 _pos)
{
 	CStage* pstage = CStageMgr::GetInst()->GetCurStage();
	// 현재 좌표
	UINT ROW = (UINT)_pos.y / TILE_SIZE;
	UINT COL = (UINT)_pos.x / TILE_SIZE;

	if (pstage->GetPosTile(ROW, COL)->CheckImgIdxToMove())
	{
		COL = ((UINT)_pos.x - 32) / TILE_SIZE;
		if (pstage->GetPosTile(ROW, COL)->CheckImgIdxToMove())
			return true;
	}
	else
		return false;
}
