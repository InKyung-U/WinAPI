#pragma once
#include "CObj.h"


class CForcePoint :
    public CObj
{
private:
    float   m_fForce;       // 주변에 영향을 줄 힘
    float   m_fMaxDistance; // 힘의 범위
    float   m_fLifeTime;    // 최대 유지시간
    float   m_fCurTime;     // 현재 생존 시간

    EOBJ_TYPE m_eTargetType; // 힘을 받게 될 물체들의 타입

public:
    void SetForce(float _force)
    {
        m_fForce = _force;
    }

    void SetDistance(float _fDistance)
    {
        m_fMaxDistance = _fDistance;
    }
    void SetLifeTime(float _fLifeTime)
    {
        m_fLifeTime = _fLifeTime;
    }
    void SetTargetType(EOBJ_TYPE _eType)
    {
        m_eTargetType = _eType;
    }


public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

    CLONE(CForcePoint);
public:
    CForcePoint();
    ~CForcePoint();
};

