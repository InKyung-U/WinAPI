#include "pch.h"
#include "CState_Dead.h"



CState_Dead::CState_Dead()
	: CState(EMON_STATE::MON_DEAD)
{
}

CState_Dead::~CState_Dead()
{
}

void CState_Dead::Enter()
{
	// Dead 애니메이션 재생

}

void CState_Dead::update()
{
	// 애니메이션 재생 끝났으면 오브젝트 삭제
	
}