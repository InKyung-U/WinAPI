#include "pch.h"
#include "Stage_G_02.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"

#include "CPanel.h"
#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"
#include "CPicture.h"
#include "CText.h"
#include "CMonster.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_G_02::Stage_G_02()
	: m_pGate01(nullptr)
	, m_pDoor01(nullptr)
	, m_pDoor02(nullptr)
	, m_pGreenKey(nullptr)
	, m_bMonsterCreate(false)
	, m_fAddTime(0.f)
{
	LoadTileFromFile(L"tile\\g_02");

}

Stage_G_02::~Stage_G_02()
{
}

void Stage_G_02::init()
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

// door
	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 19 + 32, 64.f * 5));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);

	m_pDoor02 = new CDoor;
	m_pDoor02->SetPos(Vec2(64.f * 23 + 32, 64.f * 5));
	m_pDoor02->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor02, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);

	m_pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::G_01)
		m_pObj->SetPos(Vec2(64.f * 1, 64.f * 8));
	else if (CStageMgr::GetInst()->GetPrevDoor() == 1)
	{
		CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
		doorClose->Play();
		m_pObj->SetPos(Vec2(64.f * 19 + 32, 64.f * 6 + 32));
		if (CStageMgr::GetInst()->IsHaveGreenKey())
		{
			if (CStageMgr::GetInst()->IsMonsterBroken())
			{
				if (CStageMgr::GetInst()->IsMonsterBrokenSoundPlayed() == false)
				{
					CSound* MonsterBroken = CResMgr::GetInst()->FindSound(L"Monster_broken");
					MonsterBroken->Play();
					CStageMgr::GetInst()->TurnOnMonsterBrokenSound();
				}
			}
		}
	}
	else if (CStageMgr::GetInst()->GetPrevDoor() == 2)
	{
		CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
		doorClose->Play();
		m_pObj->SetPos(Vec2(64.f * 23 + 32, 64.f * 6 + 32));
	}
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		m_pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());
	
	m_pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(m_pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(m_pObj->GetPos());
	StageAdjustment();


	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0, 64.f * 8));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// 그림
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 2 + 32, 64 * 4 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_001", L"texture\\g_bmp\\g_001.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 6 + 32, 64 * 4 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_002", L"texture\\g_bmp\\g_002.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	CObj* pic3 = new CPicture;
	pic3->SetPos(Vec2(64 * 10 + 32, 64 * 4 + 32));
	pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_003", L"texture\\g_bmp\\g_003.bmp"));
	AddObject(pic3, EOBJ_TYPE::PIC);

	CObj* pic4 = new CPicture;
	pic4->SetPos(Vec2(64 * 14 + 32, 64 * 4 + 32));
	pic4->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_004", L"texture\\g_bmp\\g_004.bmp"));
	AddObject(pic4, EOBJ_TYPE::PIC);

	CObj* pic5 = new CPicture;
	pic5->SetPos(Vec2(64 * 32 + 32, 64 * 4 + 32));
	pic5->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_005", L"texture\\g_bmp\\g_005.bmp"));
	AddObject(pic5, EOBJ_TYPE::PIC);
	

	// 텍스트
	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 2 + 32, 64 * 5 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetUIScript(L"\'프롤로그\'");
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 6 + 32, 64 * 5 + 32));
	text2->SetScale(Vec2(20, 20));
	text2->SetUIScript(L"\'제 1장\'");
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 10 + 32, 64 * 5 + 32));
	text3->SetScale(Vec2(20, 20));
	text3->SetUIScript(L"\'제 2장\'");
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	CObj* text4 = new CText;
	text4->SetPos(Vec2(64 * 14 + 32, 64 * 5 + 32));
	text4->SetScale(Vec2(20, 20));
	text4->SetUIScript(L"\'최종장\'");
	text4->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text4, EOBJ_TYPE::TEXT);

	CObj* text5 = new CText;
	text5->SetPos(Vec2(64 * 32 + 32, 64 * 5 + 32));
	text5->SetScale(Vec2(20, 20));
	text5->SetUIScript(L"\'최종장\'");
	text5->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text5, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsHaveGreenKey())
	{
		wstring str[3] = { L"초록 열쇠를 얻었다.",L"...?",L"" };
		m_pGreenKey = new CText;
		m_pGreenKey->SetPos(Vec2(64 * 32 + 32, 64 * 7 + 32));
		m_pGreenKey->SetScale(Vec2(15, 30));
		m_pGreenKey->SetScriptList(str);
		m_pGreenKey->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_key", L"texture\\g_bmp\\g_key.bmp"));
		AddObject(m_pGreenKey, EOBJ_TYPE::TEXT);

		m_pMonsterImg = new CPicture;
		m_pMonsterImg->SetPos(Vec2(64 * 35 + 32, 64 * 7 + 32));
		m_pMonsterImg->SetTexture(CResMgr::GetInst()->LoadTexture(L"monster_LStand", L"texture\\ib\\RMane_LStand.bmp"));
		AddObject(m_pMonsterImg, EOBJ_TYPE::PIC);
	}

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_G_02::update()
{
	CSound* Monster = CResMgr::GetInst()->FindSound(L"monster1");

	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::G_01);
	}

	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CSound* doorOpen = CResMgr::GetInst()->FindSound(L"door_open");
			doorOpen->Play();
			CStageMgr::GetInst()->SetPrevDoor(1);
			ChangeStage(ESTAGE_TYPE::G_03);
		}
	}
	if (((CDoor*)m_pDoor02)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CSound* doorOpen = CResMgr::GetInst()->FindSound(L"door_open");
			doorOpen->Play();
			CStageMgr::GetInst()->SetPrevDoor(2);
			ChangeStage(ESTAGE_TYPE::G_03);
		}
	}
	if (!CStageMgr::GetInst()->IsHaveGreenKey())
	{
		if (((CText*)m_pGreenKey)->IsScriptSearchDone())
		{
			CStageMgr::GetInst()->TurnOnGreenKey();
			m_pGreenKey->SetScale(Vec2(0, 0));
			m_pGreenKey->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_key_nullTex", L"texture\\nullbmp.bmp"));
			CSound* KeyGet = CResMgr::GetInst()->FindSound(L"item_get");
			KeyGet->Play();
			m_bMonsterCreate = true;
		}
	}

	if (CStageMgr::GetInst()->IsMonsterBroken() == false)
	{
		if (CStageMgr::GetInst()->IsHaveGreenKey())
		{
			if (m_bMonsterCreate && m_pMonster == nullptr)
			{
				CStageMgr::GetInst()->TurnOnEventAnimation();
				m_fAddTime += DS;

				if (m_fAddTime < 0.4f)
				{
					m_pMonsterImg->SetTexture(CResMgr::GetInst()->LoadTexture(L"monster_LWalk", L"texture\\ib\\RMane_LWalk.bmp"));
					m_pMonsterImg->AddPos(Vec2(-1, 0));
				}
				else if (m_fAddTime < 0.8f)
				{
					m_pMonsterImg->SetTexture(CResMgr::GetInst()->LoadTexture(L"monster_LStand", L"texture\\ib\\RMane_LStand.bmp"));
					m_pMonsterImg->AddPos(Vec2(-1, 0));
				}
				else if (m_fAddTime < 1.2f)
				{
				}
				else if (m_fAddTime < 1.6f)
				{
					m_pObj->AddPos(Vec2(-1, 0));
					m_pObj->GetAnimator()->Play(L"WALKRIGHT_IB");
				}
				else
					m_pObj->GetAnimator()->Play(L"STANDRIGHT_IB");

				if (3.f < m_fAddTime)
				{
					m_pMonsterImg->SetTexture(CResMgr::GetInst()->LoadTexture(L"monster_null", L"texture\\nullbmp.bmp"));

					Monster->Play();

					m_pMonster = new CMonster;
					m_pMonster->SetPos(Vec2(64 * 34 + 32, 64 * 7 + 32));
					AddObject(m_pMonster, EOBJ_TYPE::MONSTER);
					CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::MONSTER);
					m_bMonsterCreate = false;

					CStageMgr::GetInst()->TurnOffEventAnimation();

				}
			}
		}
	}

}

void Stage_G_02::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_G_02::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_G_02::Exit()
{
	if (CStageMgr::GetInst()->IsHaveGreenKey())
	{
		((CMonster*)m_pMonster)->SetHitCountZero();
	}
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::DOOR);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::HAND);
	Clear(EOBJ_TYPE::MONSTER);
	Clear(EOBJ_TYPE::UI);


}
