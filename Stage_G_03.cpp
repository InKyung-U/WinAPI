#include "pch.h"
#include "Stage_G_03.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"
#include "CMonster.h"
#include "CPicture.h"
#include "CText.h"
#include "CPanel.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_G_03::Stage_G_03()
	: m_pDoor01(nullptr)
	, m_pDoor02(nullptr)
	, m_pMonster(nullptr)
	, m_fAddTime(0.f)
{
	LoadTileFromFile(L"tile\\g_03");

}

Stage_G_03::~Stage_G_03()
{
}

void Stage_G_03::init()
{
	// UI 
	CStageMgr::GetInst()->SetRoseCount(CStageMgr::GetInst()->GetRoseCount());

	// UI 만들기
	Vec2 vScale = Vec2(120, 160);
	Vec2 vPos = Vec2(0.f, 0.f);
	// UI 1
	pParentUI = new CPanel;
	pParentUI->SetPos(vPos);
	pParentUI->SetScale(vScale);

	AddObject(pParentUI, EOBJ_TYPE::UI);

	POINT ptResolution = CCore::GetInst()->GetResolution();

	pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevDoor() == 1)
		pObj->SetPos(Vec2(64.f * 5 + 32, 64.f * 6));	
	else if (CStageMgr::GetInst()->GetPrevDoor() == 2)
		pObj->SetPos(Vec2(64.f * 13 + 32, 64.f * 6));	
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
	doorClose->Play();

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 5 + 32, 64.f * 7));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);

	m_pDoor02 = new CDoor;
	m_pDoor02->SetPos(Vec2(64.f * 13 + 32, 64.f * 7));
	m_pDoor02->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor02, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);


	text1 = new CText;
	text1->SetPos(Vec2(64 * 9 + 32, 64 * 5));
	text1->SetScale(Vec2(64.f * 2, 64.f * 2));
	if(CStageMgr::GetInst()->HaveAntPic())
		text1->SetUIScript(L"개미 그림을 바닥에 놓았습니다.");
	else
		text1->SetUIScript(L"바닥이 갈라져 있어 지나갈 수 없어...");

	if (CStageMgr::GetInst()->IsAntPicPutTile())
		text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"ant_tear1", L"texture\\g_bmp\\ant_tear1.bmp"));
	else 
		text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);
	
}

void Stage_G_03::update()
{
	CStage::update();

	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CSound* doorOpen = CResMgr::GetInst()->FindSound(L"door_open");
			doorOpen->Play();
			CStageMgr::GetInst()->SetPrevDoor(1);
			ChangeStage(ESTAGE_TYPE::G_02);
		}
	}
	if (((CDoor*)m_pDoor02)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CSound* doorOpen = CResMgr::GetInst()->FindSound(L"door_open");
			doorOpen->Play();
			CStageMgr::GetInst()->SetPrevDoor(2);
			ChangeStage(ESTAGE_TYPE::G_02);
		}
	}

	if (CStageMgr::GetInst()->IsAntPicPutTile() == false)
	{
		if (CStageMgr::GetInst()->HaveAntPic())
		{
			if (((CText*)text1)->IsScriptSearchDone())
			{
				text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_ant", L"texture\\g_bmp\\g_ant.bmp"));
				CStageMgr::GetInst()->TurnOnAntPicPutTile();
				CStageMgr::GetInst()->TurnOffAntPic();
			}
		}
	}
	else
	{
		CSound* ant = CResMgr::GetInst()->FindSound(L"PressedAnt");

		if (CStageMgr::GetInst()->returnAntPicCount() == 2)
		{
			if (64 * 10 + 32<= pObj->GetPos().x)
			{
				ant->Play();

				CStageMgr::GetInst()->SubAntPicCount();
			}
		}
		if (CStageMgr::GetInst()->returnAntPicCount() == 1)
		{
			text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"ant_tear1", L"texture\\g_bmp\\ant_tear1.bmp"));
			if (pObj->GetPos().x <= 64.f * 8)
			{
				if (CStageMgr::GetInst()->IsHaveGreenKey())
				{
					ant->Play();
					CStageMgr::GetInst()->SubAntPicCount();
				}
			}
		}
		if (CStageMgr::GetInst()->returnAntPicCount() == 0)
			text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"ant_tear2", L"texture\\g_bmp\\ant_tear2.bmp"));

	}



	if (CStageMgr::GetInst()->IsMonsterBroken() == false)
	{
		if (CStageMgr::GetInst()->IsHaveGreenKey())
		{
			m_fAddTime += DS;
			if (2.f <= m_fAddTime)
			{
				if (m_pMonster == nullptr)
				{

					m_pMonster = new CMonster;
					m_pMonster->SetPos(Vec2(64.f * 13 + 32, 64.f * 6));
					AddObject(m_pMonster, EOBJ_TYPE::MONSTER);
					CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::MONSTER);
				}
			}
		}
	}

}

void Stage_G_03::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_G_03::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_G_03::Exit()
{
	if (CStageMgr::GetInst()->IsHaveGreenKey())
	{
		CStageMgr::GetInst()->TurnOnMonsterBroken();
		((CMonster*)m_pMonster)->SetHitCountZero();
	}
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::DOOR);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::MONSTER);
	Clear(EOBJ_TYPE::UI);


}
