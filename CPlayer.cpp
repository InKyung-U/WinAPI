#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CStageMgr.h"
#include "CPathMgr.h"
#include "CUIMgr.h"

#include "CTexture.h"
#include "CTile.h"
#include "CTable.h"
#include "CStage.h"
#include "CCamera.h"
#include "CCore.h"

#include "CAnimation.h"
#include "CMovement.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"


CPlayer::CPlayer()
	: m_fSpeed(200.f)
	, m_pTex(nullptr)
	, m_eBulletType(EBULLET_TYPE::ENERGY)
	, m_fAddSecond(0.f)
	, m_kPlayerKeyState()
	, m_fMaxHitSecond(0.5f)
	, m_fAddHitSecond(0)
	, pNewSound(nullptr)
{	
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerImage", L"texture\\Player.bmp");

	// 충돌체 생성
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	pCollider->SetScale(Vec2(40.f, 80.f));

	AddComponent(pCollider);

	// Animator 생성
	CTexture* pAnimAtlasTex = CResMgr::GetInst()->LoadTexture(L"PlayerAnimation", L"texture\\ib\\ib.bmp");
	CAnimator* pAnimator = new CAnimator;
	CAnimation* pAnim = nullptr;
	pAnimator->LoadAnimation(L"animation\\player\\WALKDOWN_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALKUP_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALKRIGHT_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALKLEFT_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\STANDDOWN_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\STANDUP_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\STANDRIGHT_IB.anim");
	pAnimator->LoadAnimation(L"animation\\player\\STANDLEFT_IB.anim");

	//pAnim = pAnimator->FindAnimation(L"WALK_DOWN");
	//pAnim->Save(L"animation\\player\\");

	//pAnimator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");
	
	AddComponent(pAnimator);
	pAnimator->Play(L"STANDRIGHT_IB");

	pNewSound = CResMgr::GetInst()->FindSound(L"kutu_ib");
	pNewSound->Play(true);
	pNewSound->Stop();

	m_kPlayerKeyState = CStageMgr::GetInst()->GetKeyState();

	if(m_kPlayerKeyState == KEY::RIGHT)
		pAnimator->Play(L"STANDRIGHT_IB");
	else if (m_kPlayerKeyState == KEY::LEFT)
		pAnimator->Play(L"STANDLEFT_IB");
	else if (m_kPlayerKeyState == KEY::UP)
		pAnimator->Play(L"STANDUP_IB");
	else if (m_kPlayerKeyState == KEY::DOWN)
		pAnimator->Play(L"STANDDOWN_IB");


	// MovementComponent 생성
	//AddComponent(new CMovement);
	//GetMovement()->SetMaxXSpeed(300.f);
	//GetMovement()->SetMaxYSpeed(600.f);
	//GetMovement()->SetMass(1.f);
	//GetMovement()->EnableGravity();
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{


	Vec2 vPos = GetPos();
	UINT xTileCount = CStageMgr::GetInst()->GetCurStage()->GetTileXCount();
	UINT yTileCount = CStageMgr::GetInst()->GetCurStage()->GetTileYCount();
	UINT iStageWidth = xTileCount * TILE_SIZE;
	UINT IStageHeight = yTileCount * TILE_SIZE;

	if (CUIMgr::GetInst()->IsScriptOn())
	{
	}
	else if(CStageMgr::GetInst()->IsEventAnimationOn() == false)
	{
		if (KPRESSED(KEY::LEFT))
		{
			m_fAddSecond += DS;
			if (0.07f <= m_fAddSecond)
			{
				if (CStageMgr::GetInst()->GetCurStage()->IsTableExist())
				{
					if (CStageMgr::GetInst()->GetCurStage()->GetStageTable()->GetTableMove() == false)
					{
						if (CanIMoveNextTile(Vec2(vPos.x - 32, vPos.y + 50)))
						{
							vPos.x -= 32;
						}
					}
				}
				else
				{
					if (0 < vPos.x - 32)
					{
						if (CanIMoveNextTile(Vec2(vPos.x - 32, vPos.y + 50)))
						{
							vPos.x -= 32;
						}
					}
				}
				m_fAddSecond = 0;
			}
		}

		if (KPRESSED(KEY::RIGHT))
		{
			m_fAddSecond += DS;
			if (0.07f <= m_fAddSecond)
			{
				if (CStageMgr::GetInst()->GetCurStage()->IsTableExist())
				{
					if (CStageMgr::GetInst()->GetCurStage()->GetStageTable()->GetTableMove() == false)
					{
						if (CanIMoveNextTile(Vec2(vPos.x + 32 + 20, vPos.y + 50)))
						{						
							vPos.x += 32;
						}
					}
				}
				else
				{
					if (CanIMoveNextTile(Vec2(vPos.x + 32 + 20, vPos.y + 50)))
					{						
						vPos.x += 32;
					}
				}
				m_fAddSecond = 0;
			}
		}

		if (KPRESSED(KEY::UP))
		{
			m_fAddSecond += DS;
			if (0.07f <= m_fAddSecond)
			{
				if (CStageMgr::GetInst()->GetCurStage()->IsTableExist())
				{
					if (CStageMgr::GetInst()->GetCurStage()->GetStageTable()->GetTableMove() == false)
					{
						if (CanIMoveNextTile(Vec2(vPos.x, vPos.y - 32)))
						{
							vPos.y -= 32;
						}
					}
				}
				else
				{
					if (CanIMoveNextTile(Vec2(vPos.x, vPos.y - 32)))
					{
					
						vPos.y -= 32;
					}
				}

				m_fAddSecond = 0;
			}
		}

		if (KPRESSED(KEY::DOWN))
		{
			m_fAddSecond += DS;
			if (0.07f <= m_fAddSecond)
			{
				if (CanIMoveNextTile(Vec2(vPos.x + 20, vPos.y + 32 + 50)))
				{
					vPos.y += 32;
				}
				m_fAddSecond = 0;
			}
		}
		SetPos(vPos);

		if (KTAP(KEY::LEFT))
		{
			pNewSound = CResMgr::GetInst()->FindSound(L"kutu_ib");
			pNewSound->Play(true);

			GetAnimator()->Play(L"WALKLEFT_IB");
			m_kPlayerKeyState = KEY::LEFT;
		}
		else if (KTAP(KEY::RIGHT))
		{
			pNewSound = CResMgr::GetInst()->FindSound(L"kutu_ib");
			pNewSound->Play(true);
			GetAnimator()->Play(L"WALKRIGHT_IB");
			m_kPlayerKeyState = KEY::RIGHT;

		}
		else if (KTAP(KEY::UP))
		{
			pNewSound = CResMgr::GetInst()->FindSound(L"kutu_ib");
			pNewSound->Play(true);
			GetAnimator()->Play(L"WALKUP_IB");
			m_kPlayerKeyState = KEY::UP;

		}
		else if (KTAP(KEY::DOWN))
		{
			pNewSound = CResMgr::GetInst()->FindSound(L"kutu_ib");
			pNewSound->Play(true);
			GetAnimator()->Play(L"WALKDOWN_IB");
			m_kPlayerKeyState = KEY::DOWN;

		}

		// 키 입력이 없을때는 가만히 있는 자세로
		if (KAWAY(KEY::LEFT))
		{
			if(pNewSound != nullptr)
				pNewSound->Stop();
			GetAnimator()->Play(L"STANDLEFT_IB");
		}
		else if (KAWAY(KEY::RIGHT))
		{
			if (pNewSound != nullptr)
				pNewSound->Stop();

			GetAnimator()->Play(L"STANDRIGHT_IB");
		}
		else if (KAWAY(KEY::UP))
		{
			if (pNewSound != nullptr)
				pNewSound->Stop();

			GetAnimator()->Play(L"STANDUP_IB");
		}
		else if (KAWAY(KEY::DOWN))
		{
			if (pNewSound != nullptr)
				pNewSound->Stop();

			GetAnimator()->Play(L"STANDDOWN_IB");
		}
	}

	CStageMgr::GetInst()->SaveKeyState(m_kPlayerKeyState);
}

void CPlayer::render(HDC _dc)
{	
	// 이미지로 출력
	/*Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();
	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(_dc
		, (int)vRenderPos.x - iWidth / 2
		, (int)vRenderPos.y - iHeight / 2
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, bf);*/

	// 컴포넌트를 렌더링 한다.
	render_component(_dc);
	Vec2 wndSize = CCore::GetInst()->GetResolution();
	Vec2 cameraPos = CCamera::GetInst()->GetLookAtPos();

	if (CStageMgr::GetInst()->IsPlayerHit())
	{
		CTexture* VeilTex = CResMgr::GetInst()->LoadTexture(L"ib_hit", L"texture\\ib_hit.bmp");
		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
		m_fAddHitSecond += DS;

	
		UINT iWidth = VeilTex->Width();
		UINT iHeight = VeilTex->Height();
		float fAlpha = 0.f;
		fAlpha = (1.f - (m_fAddHitSecond / m_fMaxHitSecond));
		BLENDFUNCTION bf = {};


		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = BYTE(fAlpha * 255.f);
		bf.AlphaFormat = 0;

		if (fAlpha <= 0.f)
		{
			CStageMgr::GetInst()->TurnOffPlayerHit();
			m_fAddHitSecond = 0;
			return;
		}


		TransparentBlt(_dc
			, (int)vRenderPos.x - iWidth / 2
			, (int)vRenderPos.y - iHeight / 2
			, iWidth, iHeight
			, VeilTex->GetDC()
			, 0, 0
			, iWidth, iHeight
			, RGB(255, 0, 255));

	//	TransparentBlt(CCore::GetInst()->GetAlphaDC()
	//		, (int)vRenderPos.x - iWidth / 2
	//		, (int)vRenderPos.y - iHeight / 2
	//		, iWidth, iHeight
	//		, VeilTex->GetDC()
	//		, 0,0
	//		, VeilTex->Width(), VeilTex->Height()
	//		, RGB(255, 0, 255));
	//
	//	AlphaBlend(_dc
	//		, cameraPos.x - wndSize.x / 2
	//		, cameraPos.y - wndSize.y / 2
	//		, wndSize.x, wndSize.y
	//		, CCore::GetInst()->GetAlphaDC()
	//		, 0, 0
	//		, wndSize.x, wndSize.y
	//		, bf);
	//
	}
}


#include "CBullet.h"
#include "CGuidedBullet.h"
#include "CEnergyBullet.h"
void CPlayer::Shoot()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// 총알 생성
	CBullet* pBullet = nullptr;

	switch (m_eBulletType)
	{
	case EBULLET_TYPE::NORMAL:
	{
		pBullet = new CBullet;
		pBullet->SetScale(vScale / 2.f);
		vPos = Vec2(vPos.x, vPos.y - vScale.y / 2.f);	
		CreateObject(pBullet, EOBJ_TYPE::PLAYER_PROJECTILE, vPos);
	}
		break;
	case EBULLET_TYPE::GUIDED:
	{
		int iBulletCount = 10;
		vPos = Vec2(vPos.x, vPos.y - vScale.y / 2.f);

		for(int i = 0; i < iBulletCount; ++i)
		{
			pBullet = new CGuidedBullet;
			pBullet->SetScale(vScale / 2.f);			
			((CGuidedBullet*)pBullet)->FindTarget();
						
			Vec2 vDir = Vec2(0.f, -1.f);
			vDir = GetRotateVec(vDir, (2.f * PI * (float)i) / (float)iBulletCount);
			pBullet->SetDir(vDir);

			CreateObject(pBullet, EOBJ_TYPE::PLAYER_PROJECTILE, vPos);
		}				
	}
	break;

	case EBULLET_TYPE::ENERGY:
	{
		vPos = Vec2(vPos.x, vPos.y - vScale.y / 2.f);
		pBullet = new CEnergyBullet;

		pBullet->SetScale(vScale / 2.f);
		((CGuidedBullet*)pBullet)->FindTarget();

		pBullet->SetDir(Vec2(0.f, -1.f));
		pBullet->SetSpeed(400.f);
		CreateObject(pBullet, EOBJ_TYPE::PLAYER_PROJECTILE, vPos);
	}
		break;
	}

	
}

bool CPlayer::CanIMoveNextTile(Vec2 _pos)
{
	CStage* pstage = CStageMgr::GetInst()->GetCurStage();
	// 현재 좌표
	UINT ROW = (UINT)_pos.y / TILE_SIZE;
	UINT COL = (UINT)_pos.x / TILE_SIZE;

	if (pstage->GetPosTile(ROW, COL)->CheckImgIdxToMove())
	{
		COL = ((UINT)_pos.x - 32) / TILE_SIZE;
		if (pstage->GetPosTile(ROW, COL)->CheckImgIdxToMove())
			return true;
	}
	else
		return false;
}


void CPlayer::OnCollision(CObj* _pOtherObj)
{
}


