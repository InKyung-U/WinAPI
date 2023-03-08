#pragma once
#include "CBullet.h"

class CGuidedBullet :
    public CBullet
{
private:
    CObj* m_pTarget;
    float m_fCurAngle;
    float m_fRotateSpeed;

    
public:
    CObj* GetTarget() { return m_pTarget; }    


public:
    void update() override;
    

public:
    void FindTarget();

    CLONE(CGuidedBullet);

public:
    CGuidedBullet();
    ~CGuidedBullet();        
};

