#pragma once
#include "CStage.h"

class CTexture;
class CObj;
class CStartScript :
    public CStage
{
private:
    CTexture* m_pBackImg;
    wstring m_pScript1;
    float m_fAddTime;
    UINT    m_iScriptCount;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) ;

    void Enter() override;
    void Exit() override;


public:
    CStartScript();
    ~CStartScript();
};

