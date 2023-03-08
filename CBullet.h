#pragma once
#include "CObj.h"

struct tTailInfo
{
    Vec2        vPos;
    float       fTime;
};


class CTexture;

class CBullet :
    public CObj
{
private:
    Vec2            m_vDir;     // 이동 방향
    float           m_fSpeed;   // 속력
    CTexture*       m_pTex;
    list<tTailInfo> m_listTailInfo;
    float           m_fTailAddTime;
    

protected:   
    float           m_fAddTime;   
    

public:
    void update() override;
    void render(HDC _dc) override;
    void OnCollisionEnter(CObj* _pOther) override;


public:
    void SetTex(CTexture* _pTex){m_pTex = _pTex;}
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    Vec2 GetDir() { return m_vDir; }


    CLONE(CBullet);


public:
    CBullet();
    ~CBullet();
};

