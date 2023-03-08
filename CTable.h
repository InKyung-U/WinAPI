#pragma once
#include "CObj.h"

class CTexture;
class CTable :
    public CObj
{
private:
    CTexture* m_pTex;
    bool        m_bTableMove;
    bool        m_bMovingTable;
    float       m_fTableSec;
    Vec2        m_vTableMoveScale;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);
    void SetMovingTableOn(Vec2 _pos) 
	{
		m_bMovingTable = true;
		m_vTableMoveScale = _pos;
	}
    bool GetTableMove() { return m_bTableMove; }


public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;
    virtual void OnCollisionExit(CObj* _pOtherObj) override;

    virtual void SetTexture(CTexture* _tex) { m_pTex = _tex; }

    CLONE(CTable);

public:
    CTable();
    ~CTable();
};

