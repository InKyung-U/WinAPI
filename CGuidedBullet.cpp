#include "pch.h"
#include "CGuidedBullet.h"

#include "CStageMgr.h"
#include "CStage.h"
#include "CMonster.h"

CGuidedBullet::CGuidedBullet()
	: m_pTarget(nullptr)
	, m_fCurAngle(PI / 2.f)
	, m_fRotateSpeed(PI / 2.f)
{
	//m_vVelocity = Vec2(0.f, -600.f);
	//m_vVelocity = Vec2(cosf(PI / 4.f) * 600.f, -sinf(PI / 4.f) * 600.f);

	SetDir(Vec2(0.f, -1.f).Normalize());	
}

CGuidedBullet::~CGuidedBullet()
{
}


void CGuidedBullet::update()
{
	m_fAddTime += DS;
	if (m_fAddTime >= 5.f)
	{
		DeleteObject(this);
	}

	// 타겟이 없다면
	if (nullptr == m_pTarget)
	{
		// 위로 진행
		Vec2 vPos = GetPos();
		vPos.y -= GetSpeed()* DS;
		SetPos(vPos);

		// 타겟 검색
		FindTarget();
	}

	// 타겟이 삭제 예정상태라면, 새로운 타겟을 찾는다.
	else if (m_pTarget->IsDead())
	{
		FindTarget();
	}

	else
	{
		// =======================
		// 방향 벡터를 이용하는 방식
		// =======================
		Vec2 vTargetPos = m_pTarget->GetPos();
		Vec2 vCurPos = GetPos();

		// 목적지를 향하는 방향벡터
		Vec2 vTargetDir = vTargetPos - vCurPos;
		vTargetDir.Normalize();

		Vec2 vDir = GetDir();

		// 방향 벡터와 목적지 벡터사이에 내적을 진행
		float fCos = vDir.Dot(vTargetDir);
		float angle = acosf(fCos); // 두 벡터사이각 구함

		float RotateAngle = PI * DS;
		if (angle < RotateAngle)
		{
			RotateAngle = angle;
		}

		// 방향벡터 회전		
		Vec2 vNewDir = GetRotateVec(vDir, -RotateAngle);

		fCos = vNewDir.Dot(vTargetDir);
		float newAngle = acosf(fCos); // 두 벡터사이각 구함

		if (abs(newAngle) > abs(angle))
		{
			vNewDir = GetRotateVec(vDir, RotateAngle);
		}

		// 방향으로 이동
		vCurPos += vNewDir * GetSpeed() * DS;

		SetDir(vNewDir);
		SetPos(vCurPos);		
	}
}

void CGuidedBullet::FindTarget()
{
	CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();

	const vector<CObj*>& vecMonster = pCurStage->GetObjects(EOBJ_TYPE::MONSTER);

	if (vecMonster.empty())
	{
		m_pTarget = nullptr;
		return;
	}

	Vec2 vPos = GetPos();
	float fDistance = -1.f;

	// 모든 몬스터에 대해서 반복문 돌면서, 더 가까운 녀석을 찾아서 타겟으로 삼는다.
	for (size_t i = 0; i < vecMonster.size(); ++i)
	{
		Vec2 vMonPos = vecMonster[i]->GetPos();

		float fCurDist = vPos.GetDistance(vMonPos);

		if (fCurDist < fDistance || fDistance == -1.f)
		{
			m_pTarget = vecMonster[i];
			fDistance = fCurDist;
		}
	}	
}