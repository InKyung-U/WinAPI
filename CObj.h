#pragma once

#include "CTimeMgr.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CFSM.h"
#include "CMovement.h"

class CObj
{
private:
	wstring		m_strName;
	Vec2		m_vPos;
	Vec2		m_vScale;

	CComponent* m_arrCom[(UINT)ECOM_TYPE::END];

	bool	m_bDead;

public:
	void SetPos(Vec2 _Pos) { m_vPos = _Pos; }
	virtual void SetScale(Vec2 _scale) { m_vScale = _scale; }
	void SetName(const wstring& _strName) { m_strName = _strName; }
	void AddPos(Vec2 _Pos) { m_vPos += _Pos; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	const wstring& GetName() { return m_strName; }

	void AddComponent(CComponent* _pCom);
	CComponent* GetComponent(ECOM_TYPE _eType){return m_arrCom[(UINT)_eType];}
	CCollider* GetCollider() { return (CCollider*)m_arrCom[(UINT)ECOM_TYPE::COLIIDER]; }
	CAnimator* GetAnimator() { return (CAnimator*)m_arrCom[(UINT)ECOM_TYPE::ANIMATOR]; }
	CFSM* GetFSM() { return (CFSM*)m_arrCom[(UINT)ECOM_TYPE::FSM]; }
	CMovement* GetMovement() { return (CMovement*)m_arrCom[(UINT)ECOM_TYPE::MOVEMENT]; }

	bool IsDead() { return m_bDead; }
	

public:
	virtual void update() = 0;
	virtual void finalupdate() final; // CObj 를 상속받는 자식 클래스에서 오버라이딩 자체를 할 수 없게 문법적으로 방지함
	virtual void render(HDC _dc);

	virtual CObj* Clone() = 0;


	void render_component(HDC _dc);

	virtual void OnCollisionEnter(CObj* _pOhterObj) {};
	virtual void OnCollision(CObj* _pOtherObj) {};
	virtual void OnCollisionExit(CObj* _pOtherObj) {};

	virtual void SetTexture(CTexture* _tex) {};
	virtual void SetUIScript(const wstring& _str) {};
	virtual void SetScriptList(wstring _list[3]) {};

private:
	void SetDead(){m_bDead = true;}
	CObj& operator = (const CObj& _origin) = delete;

public:
	CObj();
	CObj(const CObj& _origin);
	virtual ~CObj();

	friend class CEventMgr;
};

