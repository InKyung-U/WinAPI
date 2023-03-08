#include "pch.h"
#include "CState_Idle.h"

#include "CStageMgr.h"

CState_Idle::CState_Idle()
	: CState(EMON_STATE::MON_IDLE)
{
}

CState_Idle::~CState_Idle()
{
}

void CState_Idle::update()
{
	if (DeadCheck())
		return;


	// 현재 상태를 실행중인 몬스터를 알아낸다.
	CMonster* pMonster = GetOwnerMonster();

	// 몬스터의 현재 위치와 탐지범위를 알아낸다.
	Vec2 vMonPos = pMonster->GetPos();
	float fDetectRange = pMonster->GetMonInfo().m_fDetectRange;

	// 플레이어를 알아낸다.
	CObj* pPlayer = CStageMgr::GetInst()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 몬스터의 탐지범위 내에 플레이어가 있는지 확인한다.
	float fDistance = vMonPos.GetDistance(vPlayerPos);

	if(fDistance < fDetectRange)
	{
		ChangeState(EMON_STATE::MON_TRACE);
	}
}