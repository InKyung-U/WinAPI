#pragma once
#include "CObj.h"

class CMonster :
    public CObj
{
private:
    tMonInfo    m_Info;
    int         m_iHitCount;
    wstring     m_sCurAnimationName;
    wstring     m_sChangeAniName;

    CAnimator* pAnimator;

public:
    void update() override;
    void render(HDC _dc) override;

    void SetHitCountZero() { m_iHitCount = 0; }

    void OnCollisionEnter(CObj* _pOtherObj) override;
    bool CanIMoveNextTile(Vec2 _pos);
    void ChangeAnimation(wstring _str) { m_sChangeAniName = _str; }

public:
    const tMonInfo& GetMonInfo() { return m_Info; }
    void SetDamage(float _fDmg){m_Info.m_fCurHP -= _fDmg;}

    virtual void PlayIdleAnimation() {}
    virtual void PlayAttackAnimation() {}


protected:
    void SetMonInfo(const tMonInfo& _info){m_Info = _info;}

public:
    CLONE(CMonster);
    

public:
    CMonster();
    ~CMonster();
};

