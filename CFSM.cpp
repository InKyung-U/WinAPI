#include "pch.h"
#include "CFSM.h"

#include "CState.h"
#include "CMonster.h"



CFSM::CFSM()
	: CComponent(ECOM_TYPE::FSM)
	, m_pCurState(nullptr)
{
}

CFSM::~CFSM()
{
	Safe_Del_Map(m_mapState);
}

void CFSM::update()
{
	assert(m_pCurState);

	m_pCurState->update();
}

void CFSM::AddState(CState* _pState)
{
	m_mapState.insert(make_pair(_pState->GetStateType(), _pState));
	_pState->m_pOwnerAI = this;
}

CState* CFSM::FindState(EMON_STATE _eState)
{
	map<EMON_STATE, CState*>::iterator iter = m_mapState.find(_eState);

	if (iter != m_mapState.end())
	{
		return iter->second;
	}

	return nullptr;
}

void CFSM::SetState(EMON_STATE _eState)
{
	m_pCurState = FindState(_eState);

	assert(m_pCurState);
}

void CFSM::ChangeState(EMON_STATE _eNextState)
{
	m_pCurState->Exit();

	m_pCurState = FindState(_eNextState);

	m_pCurState->Enter();
}


bool CFSM::CheckOwner()
{
	CObj* pOwner = GetOwner();
	CMonster* pMonster = dynamic_cast<CMonster*>(pOwner);

	if (pMonster)
	{
		return true;
	}
	else
	{
		return false;
	}	
}