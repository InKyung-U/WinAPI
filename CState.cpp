#include "pch.h"
#include "CState.h"

#include "CMonster.h"
#include "CFSM.h"

#include "CEventMgr.h"

#include "CMonster.h"

CMonster* CState::GetOwnerMonster()
{
	return (CMonster*)m_pOwnerAI->GetOwner();
}

void CState::ChangeState(EMON_STATE _eNextState)
{
	tEventInfo evn = {};
	evn.eType = EEVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)GetOwnerAI();
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(evn);
}

bool CState::DeadCheck()
{
	CMonster* pMon = GetOwnerMonster();
	if (pMon->GetMonInfo().m_fCurHP <= 0.f)
	{
		ChangeState(EMON_STATE::MON_DEAD);
		return true;
	}

	return false;
}
