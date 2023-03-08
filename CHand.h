#pragma once
#include "CObj.h"

class CHand :
    public CObj
{
private:
    wstring     m_sPlayAnimationName;
    CAnimator* m_pAnimator;
    float m_fAddTime;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);

    void PlayAnimation(wstring _str) { m_sPlayAnimationName = _str; }

public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;


    CLONE(CHand);
public:
    CHand();
    ~CHand();
};

