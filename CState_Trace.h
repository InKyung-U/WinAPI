#pragma once
#include "CState.h"
class CState_Trace :
    public CState
{

public:
    virtual void update() override;
    virtual void Enter() override;

    CLONE(CState_Trace);

public:
    CState_Trace();
    ~CState_Trace();
};

