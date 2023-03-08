#include "pch.h"
#include "CPicture.h"
#include "CTexture.h"

#include "CResMgr.h"

CPicture::CPicture()
	: m_pTex()
{
	CTexture* pAnimAtlasTex = CResMgr::GetInst()->LoadTexture(L"PlayerAnimation", L"texture\\ib\\pic02.bmp");
	CResMgr::GetInst()->LoadTexture(L"PlayerAnimation", L"texture\\ib\\subcha.bmp");
	CResMgr::GetInst()->LoadTexture(L"PlayerAnimation", L"texture\\ib\\ib.bmp");

	m_pAnimator = new CAnimator;
	CAnimation* pAnim = nullptr;
	m_pAnimator->LoadAnimation(L"animation\\stage\\M_SNEEZE_MAN.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\M_PIC_REDBALL.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\M_BALL_FALL.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\REDBALL_PIC.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\M_WINDOW.anim");
	m_pAnimator->LoadAnimation(L"animation\\stage\\M_WINDOW_HAND.anim");

	m_pAnimator->LoadAnimation(L"animation\\stage\\B_SMILE.anim");

	m_pAnimator->LoadAnimation(L"animation\\player\\MOM_WALKR.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\MOM_STANDD.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\MOM_STANDR.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\MOM_STANDUP.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\DAD_WALKR.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\DAD_STANDD.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\DAD_STANDR.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\DAD_STANDUP.anim");

	m_pAnimator->LoadAnimation(L"animation\\player\\WALKUP_IB.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\WALKRIGHT_IB.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\STANDUP_IB.anim");
	m_pAnimator->LoadAnimation(L"animation\\player\\STANDRIGHT_IB.anim");

	AddComponent(m_pAnimator);
}

CPicture::~CPicture()
{
}

void CPicture::update()
{

	if (m_sPlayAnimationName.size() != 0)
	{
		m_pAnimator->Play(m_sPlayAnimationName);
	}
}

void CPicture::render(HDC _dc)
{
	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, vRenderPos.x - iWidth / 2
		, vRenderPos.y - iHeight / 2
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));

	render_component(_dc);
}

void CPicture::SetScale(Vec2 _scale)
{
}

void CPicture::OnCollisionEnter(CObj* _pOtherObj)
{
}
