#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
public:
    virtual void MouseLbtnClicked(Vec2 _vMousePos);   
    virtual void update() override;

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

