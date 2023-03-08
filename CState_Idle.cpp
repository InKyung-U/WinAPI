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


	// ���� ���¸� �������� ���͸� �˾Ƴ���.
	CMonster* pMonster = GetOwnerMonster();

	// ������ ���� ��ġ�� Ž�������� �˾Ƴ���.
	Vec2 vMonPos = pMonster->GetPos();
	float fDetectRange = pMonster->GetMonInfo().m_fDetectRange;

	// �÷��̾ �˾Ƴ���.
	CObj* pPlayer = CStageMgr::GetInst()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ������ Ž������ ���� �÷��̾ �ִ��� Ȯ���Ѵ�.
	float fDistance = vMonPos.GetDistance(vPlayerPos);

	if(fDistance < fDetectRange)
	{
		ChangeState(EMON_STATE::MON_TRACE);
	}
}