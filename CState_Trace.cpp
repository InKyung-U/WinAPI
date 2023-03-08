#include "pch.h"
#include "CState_Trace.h"

#include "CStageMgr.h"
#include "CTimeMgr.h"

CState_Trace::CState_Trace()
	: CState(EMON_STATE::MON_TRACE)
{
}

CState_Trace::~CState_Trace()
{
}

// 추적상태로 전환되는 첫 시점에 호출
void CState_Trace::Enter()
{
	// 몬스터를 가져와서 관련 애니메이션 재생 호출 명령
}


void CState_Trace::update()
{
	if (DeadCheck())
		return;


	// 플레이어를 쫒아간다.

	// 현재 상태를 실행중인 몬스터를 알아낸다.
	CMonster* pMonster = GetOwnerMonster();

	// 몬스터의 현재 위치와 탐지범위를 알아낸다.
	Vec2 vMonPos = pMonster->GetPos();
	float fDetectRange = pMonster->GetMonInfo().m_fDetectRange;
	float fSpeed = pMonster->GetMonInfo().m_fSpeed;

	// 플레이어를 알아낸다.
	CObj* pPlayer = CStageMgr::GetInst()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 몬스터에서 플레이어를 향한 방향을 알아낸다.
	Vec2 vDir = vPlayerPos - vMonPos;
	vDir.Normalize();

	// 몬스터를 플레이어를 향해서 이동시킨다.
	if (abs(vDir.x) > abs(vDir.y))
	{
		if (vDir.x > 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_R");
				vMonPos.x += vDir.x * fSpeed * DS;
			}
			else
			{
			}
		}
		else if (vDir.x <= 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_L");
				vMonPos.x += vDir.x * fSpeed * DS;
			}
			else
			{
			}
		}
	}
	else if(abs(vDir.x) <= abs(vDir.y))
	{
		if (vDir.y > 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y + 32)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_UD");
				vMonPos.y += vDir.y * fSpeed * DS;
			}
			else
			{
			}
		}
		else if (vDir.y <= 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y - 32)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_UD");
				vMonPos.y += vDir.y * fSpeed * DS;
			}
			else
			{
			}
		}
	}
	//vMonPos += vDir * fSpeed * DS;
	pMonster->SetPos(vMonPos);
	//if (vDir.y < 0) // ++
	//{
	//	pMonster->ChangeAnimation(L"RMANE_WALK_UD");
	//
	//	if(vDir.x < 0)
	//		pMonster->ChangeAnimation(L"RMANE_WALK_L");
	//}

	

	// 만약 플레이어가 공격범위 안으로 들어오면 ==> 공격상태로 변경

	// 플레이어가 탐지범위 이상으로 벗어나면
	// 탐지 중단 ==> 스폰지점으로 되돌아감 ==> Idle

	
	// 만약 몬스터의 HP 가 0 이하라면
	// ==> Dead

}
