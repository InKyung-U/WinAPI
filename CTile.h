#pragma once
#include "CObj.h"

class CTexture;

class CTile :
    public CObj
{
private:
    CTexture*   m_pAtlas;
    int         m_iImgIdx;   

public:
    void update() override;
    void render(HDC _dc) override;    

public:
    void SetImgIdx(int _iIdx){m_iImgIdx = _iIdx;}
    void AddImgIdx();

    bool CheckImgIdxToMove();

    bool IsMouseOn(Vec2 _vMouseRealPos);
  
    CLONE(CTile);

public:
    virtual void SaveToFile(FILE* _pFile);
    virtual void LoadFromFile(FILE* _pFile);
    
public:
    CTile();
    ~CTile();
};

