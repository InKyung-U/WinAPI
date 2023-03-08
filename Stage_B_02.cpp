#include "pch.h"
#include "Stage_B_02.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CDoor.h"
#include "CText.h"
#include "CUI.h"
#include "CPanel.h"
#include "CScript.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_B_02::Stage_B_02()
	: m_pGate01(nullptr)
	, m_pObj(nullptr)
	, m_fAddTime(0.f)
{
	LoadTileFromFile(L"tile\\b_02");
}

Stage_B_02::~Stage_B_02()
{
}

void Stage_B_02::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	m_pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::B_01)
		m_pObj->SetPos(Vec2(64.f * 18, 64.f * 9));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::B_00)
		m_pObj->SetPos(Vec2(64.f * 18, 64.f * 9));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::G_01)
	{
		CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
		doorClose->Play();
		m_pObj->SetPos(Vec2(64.f * 7 + 32, 64.f * 7));
	}
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		m_pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	m_pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(m_pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(m_pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 20 - 32, 64.f * 9));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);


	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 7 + 32, 64.f * 6));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	if (CStageMgr::GetInst()->IsHaveBlueKey())
	{
		DoorText = new CText;
		DoorText->SetPos(Vec2(64.f * 7 + 32, 64.f * 6));
		DoorText->SetScale(Vec2(64.f, 64.f * 2));
		DoorText->SetUIScript(L"파란 열쇠를 사용했다.");
		DoorText->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullTex", L"texture\\nullbmp.bmp"));
		AddObject(DoorText, EOBJ_TYPE::TEXT);
	}
	else
	{
		DoorText = new CText;
		DoorText->SetPos(Vec2(64.f * 7 + 32, 64.f * 6));
		DoorText->SetScale(Vec2(64.f, 64.f * 2));
		DoorText->SetUIScript(L"문이 잠겨있다..");
		DoorText->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullTex", L"texture\\nullbmp.bmp"));
		AddObject(DoorText, EOBJ_TYPE::TEXT);
	}

	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 13 + 32, 64 * 5 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_03", L"texture\\b_bmp\\b_03.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 13 + 32, 64 * 6 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetUIScript(L"\'??? 문양의 물고기\' \n어려워서 읽을 수 없는 글자가 있다...");
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_B_02::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::B_00);
	}

	if (CStageMgr::GetInst()->IsBlueDoorOpen())
	{
		if (KTAP(KEY::UP))
		{
			ChangeStage(ESTAGE_TYPE::G_01);
			CSound* doorOpen = CResMgr::GetInst()->FindSound(L"door_open");
			doorOpen->Play();
		}
	}
	
	Vec2 vPos = m_pObj->GetPos();

	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			if (CStageMgr::GetInst()->IsHaveBlueKey())
			{
				CSound* useKey = CResMgr::GetInst()->FindSound(L"key");
				useKey->Play();				
				CStageMgr::GetInst()->OpenBlueDoor();
				CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);
				CStageMgr::GetInst()->TurnOffBlueKey();
				
			}
			else
			{
				CSound* doorNotOpen = CResMgr::GetInst()->FindSound(L"door_not_open");
				doorNotOpen->Play();
			}
		}
	}
	if (((CText*)DoorText)->IsScriptOn())
	{
		if (CStageMgr::GetInst()->IsHaveBlueKey() == false)
		{
			CSound* doorNotOpen = CResMgr::GetInst()->FindSound(L"door_not_open");
			doorNotOpen->Play();
		}
	}

	/*if (KTAP(KEY::SPACE))
	{
		CUI* ps = nullptr;
		ps = new CScript;
		AddObject(ps, EOBJ_TYPE::UI);
	}*/

	
}

void Stage_B_02::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_B_02::Enter()
{
	init();

	if (CStageMgr::GetInst()->IsPlayerHaveRose())
	{
		// UI 만들기
		Vec2 vScale = Vec2(120, 160);
		Vec2 vPos = Vec2(0.f, 0.f);
		CUI* pParentUI = nullptr;
		// UI 1
		pParentUI = new CPanel;
		pParentUI->SetPos(vPos);
		pParentUI->SetScale(vScale);
		AddObject(pParentUI, EOBJ_TYPE::UI);
	}

	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_B_02::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::DOOR);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::UI);



}
