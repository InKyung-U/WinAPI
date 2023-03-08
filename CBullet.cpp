#include "pch.h"
#include "CBullet.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CMonster.h"

CBullet::CBullet()
	: m_fSpeed(1000.f)
	, m_fAddTime(0.f)
	, m_fTailAddTime(0.f)
	, m_pTex(nullptr)
{	
	CCollider* pCollider = new CCollider;
	pCollider->SetScale(Vec2(Vec2(40.f, 40.f)));
	AddComponent(pCollider);

	m_pTex = CResMgr::GetInst()->LoadTexture(L"Bullet_01", L"texture\\missile1.bmp");
}

CBullet::~CBullet()
{

}

void CBullet::update()
{
	Vec2 vPos = GetPos();
	vPos.y -= m_fSpeed * DS;
	SetPos(vPos);

	m_fAddTime += DS;
	if (m_fAddTime >= 4.f)
	{
		DeleteObject(this);
	}	
}

void CBullet::render(HDC _dc)
{
	m_fTailAddTime += DS;
	if (m_fTailAddTime > 0.01f)
	{
		m_listTailInfo.push_front(tTailInfo{ GetPos(), CTimeMgr::GetInst()->GetCurTime() });
		m_fTailAddTime = 0.f;
	}


	// render tail
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(120, 255, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(120, 255, 0));
	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Vec2 vTailScale = Vec2(15.f, 15.f);

	float fCurTime = CTimeMgr::GetInst()->GetCurTime();
	list<tTailInfo>::iterator iter = m_listTailInfo.begin();
	int i = 0;
	for (; iter != m_listTailInfo.end();)
	{
		if (fCurTime >= iter->fTime + 1.f)
		{
			iter = m_listTailInfo.erase(iter);
		}
		else
		{	
			Vec2 vCurScale = vTailScale - (float)i;
			if (vCurScale.x < 0)
				vCurScale.x = 0;
			if(vCurScale.y < 0)
				vCurScale.y = 0;
			
			if ( !(vCurScale.x == 0.f && vCurScale.y == 0.f))
			{
				Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(iter->vPos);

				Rectangle(_dc
					, int(vRenderPos.x - vCurScale.x / 2.f)
					, int(vRenderPos.y - vCurScale.y / 2.f)
					, int(vRenderPos.x + vCurScale.x / 2.f)
					, int(vRenderPos.y + vCurScale.y / 2.f));
			}
			
			++iter;			
		}
		++i;
	}


	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);


	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	TransparentBlt(_dc
		, (int)vRenderPos.x - iWidth / 2
		, (int)vRenderPos.y - iHeight / 2
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));


	render_component(_dc);
}

void CBullet::OnCollisionEnter(CObj* _pOther)
{
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther);

	if (nullptr != pMonster)
	{
		//DeleteObject(this);
	}
}
