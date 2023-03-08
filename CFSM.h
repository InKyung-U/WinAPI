#pragma once
#include "CComponent.h"

class CState;

class CFSM :
    public CComponent
{
private:
    map<EMON_STATE, CState*>    m_mapState;
    CState*                     m_pCurState;

public:
    virtual void update() override;
    CLONE(CFSM);


public:
    void AddState(CState* _pState);
    CState* FindState(EMON_STATE _eState);
    void SetState(EMON_STATE _eState);   

    void ChangeState(EMON_STATE _eNextState);


public:
    virtual bool CheckOwner() override;

public:
    CFSM();
    ~CFSM();
};

