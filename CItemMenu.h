#pragma once
#include "CStage.h"

class CTexture;
class CItemMenu :
    public CStage
{
private:
    CTexture* m_pMenuTex;
    CTexture* m_pCharTex;

    CTexture* m_pItem1;
    CTexture* m_pItem2;
    CTexture* m_pItem3;



public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    CItemMenu();
    ~CItemMenu();
};

