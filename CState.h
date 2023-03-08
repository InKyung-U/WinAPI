#pragma once

#include "CMonster.h"

class CFSM;

class CState
{
private:
	const EMON_STATE	m_eState;
	CFSM*				m_pOwnerAI;

public:
	virtual void update() = 0;
	virtual CState* Clone() = 0;

public:
	EMON_STATE GetStateType() { return m_eState; }
	CFSM* GetOwnerAI() { return m_pOwnerAI; }
	CMonster* GetOwnerMonster();


	virtual void Enter() {}
	virtual void Exit() {};

	void ChangeState(EMON_STATE _eNextState);

	bool DeadCheck();


public:
	CState(EMON_STATE _State)
		: m_eState(_State)
		, m_pOwnerAI(nullptr)
	{}

	~CState()
	{}

	friend class CFSM;
};

