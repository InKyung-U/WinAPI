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

	// 타겟이 없다면
	if (nullptr == GetTarget())
	{	
		// 방향을 유지한 채 속도를 키워서 이동한다
		Vec2 vPos = GetPos();
		float fSpeed = GetSpeed() + DS * (m_fForceSize / m_fMass);

		// 최대속도 제한
		if (fSpeed > m_fMaxSpeed)
		{
			fSpeed = m_fMaxSpeed;
		}

		SetSpeed(fSpeed);

		vPos += GetDir() * GetSpeed() * DS;
		SetPos(vPos);

		// 타겟 검색
		FindTarget();
	}

	// 타겟이 삭제 예정상태라면, 새로운 타겟을 찾는다.
	else if (GetTarget()->IsDead())
	{
		FindTarget();
	}

	else
	{
		// 타겟을 향해서 힘을 준다.
		Vec2 vTargetDir = GetTarget()->GetPos() - GetPos();
		vTargetDir.Normalize();

		m_vForce += vTargetDir * m_fForceSize;
		Vec2 vAcceleration = m_vForce / m_fMass;

		Vec2 vDir = GetDir();
		float fSpeed = GetSpeed();

		Vec2 vVelocity = (vDir * fSpeed) + vAcceleration * DS;

		// 최대속도 제한
		if (vVelocity.GetLength() > m_fMaxSpeed)
		{
			vVelocity = vVelocity.Normalize() * m_fMaxSpeed;
		}

		SetSpeed(vVelocity.GetLength());
		SetDir(vVelocity.Normalize());

		// 이동
		Vec2 vPos = GetPos();
		vPos += GetDir() * GetSpeed() * DS;
		SetPos(vPos);
	}
}
