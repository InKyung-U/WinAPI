#pragma once
#include "CComponent.h"


class CCollider :
    public CComponent
{
public:
    static UINT g_iNextID;

private:
    Vec2        m_vOffsetPos;
    Vec2        m_vScale;
    Vec2        m_vFinalPos;
    const UINT  m_iColID;
        
    int         m_iCollisionCount;

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void SetOffsetPos(Vec2 _vPos){m_vOffsetPos = _vPos;}
    void SetScale(Vec2 _vScale){m_vScale = _vScale;}
    Vec2 GetOffsetPos(){return m_vOffsetPos;}
    Vec2 GetScale(){return m_vScale;}
    Vec2 GetFinalPos(){return m_vFinalPos;}
    UINT GetID() { return m_iColID; }

    void OnCollisionEnter(CCollider* _pCollider);
    void OnCollision(CCollider* _pCollider);
    void OnCollisionExit(CCollider* _pCollider);

public:
    CCollider& operator =(const CCollider& _origin) = delete;
    CLONE(CCollider);

public:
    CCollider();
    CCollider(const CCollider& _origin);
    ~CCollider();
};

