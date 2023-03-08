#include "pch.h"
#include "CState_Attack.h"



CState_Attack::CState_Attack()
	: CState(EMON_STATE::MON_ATTACK)
{
}

CState_Attack::~CState_Attack()
{
}

void CState_Attack::update()
{
	if (DeadCheck())
		return;


}