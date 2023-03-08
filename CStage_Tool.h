#pragma once
#include "CStage.h"

enum class TOOL_MODE
{
    TILE,
    OBJECT,
    ANIMATION,
    NONE,
};

class CTile;

class CStage_Tool :
    public CStage
{
private:
    TOOL_MODE   m_eMode;
    HMENU       m_hMenu;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    void Proc(UINT _id);


private:
    void update_tile();

    

    void PopupCreateTile();
    void SaveTile();    
    void LoadTile();

    CTile* GetTile(Vec2 _vMousePos);



public:
    CStage_Tool();
    ~CStage_Tool();
};

