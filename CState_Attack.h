#pragma once
#include "CState.h"
class CState_Attack :
    public CState
{

public:
    virtual void update() override;

    CLONE(CState_Attack);

public:
    CState_Attack();
    ~CState_Attack();
};

