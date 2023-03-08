#pragma once

class CObj;

class CComponent
{
private:
	const ECOM_TYPE	m_eType;  // 컴포넌트 타입 값
	CObj*			m_pOwner; // 컴포넌트를 소유하고 있는 본체 오브젝트 주소

public:
	ECOM_TYPE GetType(){return m_eType;}
	CObj* GetOwner() { return m_pOwner; }

public:
	virtual void update() = 0;
	virtual void render(HDC _dc) {}

	virtual bool CheckOwner() { return true; }
	virtual CComponent* Clone() = 0;

public:
	CComponent(ECOM_TYPE _eType);
	virtual ~CComponent();

	friend class CObj;
};

