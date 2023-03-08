#pragma once
#include "CUI.h"

class CTexture;
class CPanel :
    public CUI
{
private:
    CTexture* m_pUITex;

public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    virtual void MouseLbtnClicked(Vec2 _vMousePos) override;

    CLONE(CPanel);

public:
    CPanel();
    ~CPanel();
};

