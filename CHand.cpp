#include "pch.h"
#include "CHand.h"

#include "CResMgr.h"
#include "CStageMgr.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CHand::CHand()
	: m_sPlayAnimationName{}
	, m_pAnimator()
	, m_fAddTime(0.f)
{
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	pCollider->SetScale(Vec2(80.f, 40.f));

	AddComponent(pCollider);

	// Animator »ý¼º
	CTexture* pAnimAtlasTex = CResMgr::GetInst()->LoadTexture(L"PlayerAnimation", L"texture\\ib\\green01.bmp");
	m_pAnimator = new CAnimator;
	CAnimation* pAnim = nullptr;
	m_pAnimator->LoadAnimation(L"animation\\stage\\G_HANDL_SWING.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\G_HANDLEFT_POPUP.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\G_HANDR_SWING.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\G_HANDRIGHT_POPUP.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\G_HANDUP_POPUP.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\G_HANDUP_SWING.anim");

	AddComponent(m_pAnimator);

	m_pAnimator->Play(L"G_HANDL_SWING");

}

CHand::~CHand()
{
}

void CHand::update()
{
	if (m_sPlayAnimationName.size() != 0)
	{
		m_pAnimator->Play(m_sPlayAnimationName);
	}

	m_fAddTime += DS;
	if (0.4f <= m_fAddTime)
	{
		if (m_sPlayAnimationName == L"G_HANDLEFT_POPUP")
			m_pAnimator->Play(L"G_HANDL_SWING");
		if (m_sPlayAnimationName == L"G_HANDRIGHT_POPUP")
			m_pAnimator->Play(L"G_HANDR_SWING");
		if (m_sPlayAnimationName == L"G_HANDUP_POPUP")
		{
			m_pAnimator->Play(L"G_HANDUP_SWING");
		}
	}
}

void CHand::render(HDC _dc)
{
	render_component(_dc);
}

void CHand::SetScale(Vec2 _scale)
{
}

void CHand::OnCollisionEnter(CObj* _pOtherObj)
{
	CSound* Hit = CResMgr::GetInst()->FindSound(L"PlayerHit");
	Hit->Play();
	CStageMgr::GetInst()->SubRoseCount();
	CStageMgr::GetInst()->TurnOnPlayerHit();
}
