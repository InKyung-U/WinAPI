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
		float fDist = vDist.GetLength(); // 포스 중심위치와 물체간의 거리

		// 힘의 범위 밖이면 continue
		if (nullptr == vecObj[i]->GetMovement() || m_fMaxDistance < fDist)
			continue;

		// 힘의 범위 안일 경우 힘을 준다.
		// 힘의 중심에 가까울 수록 1, 최대 거리에는 0 의 힘을 준다(비율 값)
		float fRatio = 1.f - (fabs(fDist) / m_fMaxDistance);

		// 힘의 방향은 힘의 중심위치에서 물체를 향하는 방향
		Vec2 vForceDir = vecObj[i]->GetPos() - GetPos();
		vForceDir.Normalize();
		vForceDir *= m_fForce * fRatio;

		vecObj[i]->GetMovement()->AddForce(vForceDir);
	}
}

void CForcePoint::render(HDC _dc)
{
	// 렌더링 될 위치
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
