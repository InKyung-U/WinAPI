#pragma once
#include "CState.h"
class CState_Idle :
    public CState
{
private:

public:
    virtual void update() override;

    CLONE(CState_Idle);

public:
    CState_Idle();
    ~CState_Idle();
};

