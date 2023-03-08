#include "pch.h"
#include "CForcePoint.h"

#include "CCore.h"
#include "CStageMgr.h"
#include "CStage.h"

#include "CMovement.h"

CForcePoint::CForcePoint()
	: m_fMaxDistance(0.f)
	, m_fLifeTime(0.f)
	, m_fCurTime(0.f)
{
}

CForcePoint::~CForcePoint()
{
}

void CForcePoint::update()
{
	m_fCurTime += DS;

	if (m_fLifeTime < m_fCurTime)
	{
		DeleteObject(this);
	}

	if (EOBJ_TYPE::END == m_eTargetType)
		return;

	const vector<CObj*>& vecObj = CStageMgr::GetInst()->GetCurStage()->GetObjects(m_eTargetType);

	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		Vec2 vDist = GetPos() - vecObj[i]->GetPos();
		float fDist = vDist.GetLength(); // ���� �߽���ġ�� ��ü���� �Ÿ�

		// ���� ���� ���̸� continue
		if (nullptr == vecObj[i]->GetMovement() || m_fMaxDistance < fDist)
			continue;

		// ���� ���� ���� ��� ���� �ش�.
		// ���� �߽ɿ� ����� ���� 1, �ִ� �Ÿ����� 0 �� ���� �ش�(���� ��)
		float fRatio = 1.f - (fabs(fDist) / m_fMaxDistance);

		// ���� ������ ���� �߽���ġ���� ��ü�� ���ϴ� ����
		Vec2 vForceDir = vecObj[i]->GetPos() - GetPos();
		vForceDir.Normalize();
		vForceDir *= m_fForce * fRatio;

		vecObj[i]->GetMovement()->AddForce(vForceDir);
	}
}

void CForcePoint::render(HDC _dc)
{
	// ������ �� ��ġ
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	
	HPEN hPrevPen = (HPEN)SelectObject(_dc, CCore::GetInst()->GetBluePen());
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, GetStockObject(HOLLOW_BRUSH));

	Ellipse(_dc, (int)(vPos.x - m_fMaxDistance)
				,(int)(vPos.y - m_fMaxDistance)
				,(int)(vPos.x + m_fMaxDistance)
				,(int)(vPos.y + m_fMaxDistance));	

	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);
}
