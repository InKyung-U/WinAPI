#pragma once
#include "CObj.h"

class CTexture;
class CAnimator;
class CPicture :
    public CObj
{
private:
    CTexture*   m_pTex;
    wstring     m_sPlayAnimationName;
    CAnimator*   m_pAnimator;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);

    void PlayAnimation(wstring _str) { m_sPlayAnimationName = _str; }

public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;
    virtual void SetTexture(CTexture* _tex) { m_pTex = _tex; }


    CLONE(CPicture);
public:
    CPicture();
    ~CPicture();
};

