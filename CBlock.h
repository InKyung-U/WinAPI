#pragma once
#include "CObj.h"
class CBlock :
    public CObj
{
private:
 
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);



public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;
    virtual void OnCollisionExit(CObj* _pOtherObj) override;

    CLONE(CBlock);

public:
    CBlock();
    ~CBlock();
};

