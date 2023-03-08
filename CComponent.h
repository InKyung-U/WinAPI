#pragma once

class CObj;

class CComponent
{
private:
	const ECOM_TYPE	m_eType;  // ������Ʈ Ÿ�� ��
	CObj*			m_pOwner; // ������Ʈ�� �����ϰ� �ִ� ��ü ������Ʈ �ּ�

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

