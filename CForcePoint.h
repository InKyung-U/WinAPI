#pragma once
#include "CObj.h"


class CForcePoint :
    public CObj
{
private:
    float   m_fForce;       // �ֺ��� ������ �� ��
    float   m_fMaxDistance; // ���� ����
    float   m_fLifeTime;    // �ִ� �����ð�
    float   m_fCurTime;     // ���� ���� �ð�

    EOBJ_TYPE m_eTargetType; // ���� �ް� �� ��ü���� Ÿ��

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

