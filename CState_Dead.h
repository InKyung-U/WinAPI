#pragma once
#include "CState.h"

class CState_Dead
	: public CState
{

public:
    virtual void update() override;
    virtual void Enter() override;

    CLONE(CState_Dead);



public:
    CState_Dead();
    ~CState_Dead();
};

