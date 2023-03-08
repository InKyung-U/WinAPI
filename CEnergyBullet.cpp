#include "pch.h"
#include "CEnergyBullet.h"

CEnergyBullet::CEnergyBullet()
	: m_fMass(1.f)
	, m_fMaxSpeed(800.f)
	, m_fForceSize(1500.f)
{
}

CEnergyBullet::~CEnergyBullet()
{
}

void CEnergyBullet::update()
{
	m_vForce = Vec2(0.f, 0.f);

	m_fAddTime += DS;
	if (m_fAddTime >= 30.f)
	{
		DeleteObject(this);
	}

	// Ÿ���� ���ٸ�
	if (nullptr == GetTarget())
	{	
		// ������ ������ ä �ӵ��� Ű���� �̵��Ѵ�
		Vec2 vPos = GetPos();
		float fSpeed = GetSpeed() + DS * (m_fForceSize / m_fMass);

		// �ִ�ӵ� ����
		if (fSpeed > m_fMaxSpeed)
		{
			fSpeed = m_fMaxSpeed;
		}

		SetSpeed(fSpeed);

		vPos += GetDir() * GetSpeed() * DS;
		SetPos(vPos);

		// Ÿ�� �˻�
		FindTarget();
	}

	// Ÿ���� ���� �������¶��, ���ο� Ÿ���� ã�´�.
	else if (GetTarget()->IsDead())
	{
		FindTarget();
	}

	else
	{
		// Ÿ���� ���ؼ� ���� �ش�.
		Vec2 vTargetDir = GetTarget()->GetPos() - GetPos();
		vTargetDir.Normalize();

		m_vForce += vTargetDir * m_fForceSize;
		Vec2 vAcceleration = m_vForce / m_fMass;

		Vec2 vDir = GetDir();
		float fSpeed = GetSpeed();

		Vec2 vVelocity = (vDir * fSpeed) + vAcceleration * DS;

		// �ִ�ӵ� ����
		if (vVelocity.GetLength() > m_fMaxSpeed)
		{
			vVelocity = vVelocity.Normalize() * m_fMaxSpeed;
		}

		SetSpeed(vVelocity.GetLength());
		SetDir(vVelocity.Normalize());

		// �̵�
		Vec2 vPos = GetPos();
		vPos += GetDir() * GetSpeed() * DS;
		SetPos(vPos);
	}
}
