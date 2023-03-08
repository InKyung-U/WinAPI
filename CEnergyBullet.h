#pragma once

#include "CGuidedBullet.h"

class CEnergyBullet :
    public CGuidedBullet
{
private:
    Vec2        m_vForce;
    float       m_fMass;

    float       m_fMaxSpeed;
    float       m_fForceSize;

public:
    void update() override;

    CLONE(CEnergyBullet);

public:
    CEnergyBullet();
    ~CEnergyBullet();
};

