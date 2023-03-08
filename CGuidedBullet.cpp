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

	// Ÿ���� ���ٸ�
	if (nullptr == m_pTarget)
	{
		// ���� ����
		Vec2 vPos = GetPos();
		vPos.y -= GetSpeed()* DS;
		SetPos(vPos);

		// Ÿ�� �˻�
		FindTarget();
	}

	// Ÿ���� ���� �������¶��, ���ο� Ÿ���� ã�´�.
	else if (m_pTarget->IsDead())
	{
		FindTarget();
	}

	else
	{
		// =======================
		// ���� ���͸� �̿��ϴ� ���
		// =======================
		Vec2 vTargetPos = m_pTarget->GetPos();
		Vec2 vCurPos = GetPos();

		// �������� ���ϴ� ���⺤��
		Vec2 vTargetDir = vTargetPos - vCurPos;
		vTargetDir.Normalize();

		Vec2 vDir = GetDir();

		// ���� ���Ϳ� ������ ���ͻ��̿� ������ ����
		float fCos = vDir.Dot(vTargetDir);
		float angle = acosf(fCos); // �� ���ͻ��̰� ����

		float RotateAngle = PI * DS;
		if (angle < RotateAngle)
		{
			RotateAngle = angle;
		}

		// ���⺤�� ȸ��		
		Vec2 vNewDir = GetRotateVec(vDir, -RotateAngle);

		fCos = vNewDir.Dot(vTargetDir);
		float newAngle = acosf(fCos); // �� ���ͻ��̰� ����

		if (abs(newAngle) > abs(angle))
		{
			vNewDir = GetRotateVec(vDir, RotateAngle);
		}

		// �������� �̵�
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

	// ��� ���Ϳ� ���ؼ� �ݺ��� ���鼭, �� ����� �༮�� ã�Ƽ� Ÿ������ ��´�.
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