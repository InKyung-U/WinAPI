#pragma once
#include "CObj.h"
class CGate :
    public CObj
{
private:
    bool m_bTouchGate;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);
    bool IsGateTouched() { return m_bTouchGate; }

public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;

    CLONE(CGate);
public:
    CGate();
    ~CGate();
};

