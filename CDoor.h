#pragma once
#include "CObj.h"
class CDoor :
    public CObj
{
private:
    bool m_bIsDoorEnter;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);

    bool IsDoorEnter() { return m_bIsDoorEnter; }

public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;
    virtual void OnCollisionExit(CObj* _pOtherObj) override;


    CLONE(CDoor);
public:
    CDoor();
    ~CDoor();
};

