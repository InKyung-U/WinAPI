#include "pch.h"
#include "Stage_M_1F_00.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CTexture.h"
#include "CPicture.h"
#include "CText.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_M_1F_00::Stage_M_1F_00()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
{
	LoadTileFromFile(L"tile\\m_1F_00");

	CResMgr::GetInst()->LoadTexture(L"table", L"texture\\M_objectbmp\\탁자.bmp");
	CResMgr::GetInst()->LoadTexture(L"poster", L"texture\\M_objectbmp\\포스터.bmp");
	CResMgr::GetInst()->LoadTexture(L"paper", L"texture\\M_objectbmp\\팜플렛.bmp");
}

Stage_M_1F_00::~Stage_M_1F_00()
{
}

void Stage_M_1F_00::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_01)
		pObj->SetPos(Vec2(64.f * 19, 64.f * 10));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_01_02)
		pObj->SetPos(Vec2(64.f * 19, 64.f * 10));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_2F_01)
		pObj->SetPos(Vec2(64.f * 16 + 32, 64.f * 2));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::STARTANIMATION)
	{
		pObj->SetPos(Vec2(64.f * 9, 64.f * 9));
	}
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	//pObj->SetPos(Vec2(64.f * 9, 64.f * 9));

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	// Gate 배치
	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(20*64 + 20, 640));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(16*64 + 32, 0));
	m_pGate02->SetScale(Vec2(64.f * 3, 64.f * 1));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);


	// 입구막는거
	mainGate = new CText;
	mainGate->SetPos(Vec2(64 * 0, 64 * 10));
	mainGate->SetScale(Vec2(64, 64 * 4));
	if (CStageMgr::GetInst()->IsMuseumEventOn())
		mainGate->SetUIScript(L"출입문이 열리지 않아...");
	else
		mainGate->SetUIScript(L" 마음대로 나가면 안 돼.");
	mainGate->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));
	AddObject(mainGate, EOBJ_TYPE::TEXT);

	// 오브젝트
	CObj* window = new CPicture;
	window->SetPos(Vec2(64 * 10 + 32, 64 * 4 + 32));
	window->SetTexture(CResMgr::GetInst()->LoadTexture(L"poster", L"texture\\M_objectbmp\\포스터.bmp"));
	AddObject(window, EOBJ_TYPE::PIC);

	CObj* table = new CPicture;
	table->SetPos(Vec2(64 * 10 + 32, 64 * 8 + 20));
	table->SetTexture(CResMgr::GetInst()->LoadTexture(L"table", L"texture\\M_objectbmp\\탁자.bmp"));
	AddObject(table, EOBJ_TYPE::PIC);

	wstring str[3] = { L"팸플릿이 놓여있다."
	, L"조작 방법\n* SPACE키 - 대화, 조사, 결정 \n* I키 - 소지 아이템 확인"
	, L""};
	CObj* paper = new CText;
	paper->SetPos(Vec2(64 * 8 + 32, 64 * 8 + 30));
	paper->SetScale(Vec2(30, 30));
	paper->SetUIScript(L" 팸플릿이 놓여있다.");
	paper->SetTexture(CResMgr::GetInst()->LoadTexture(L"paper", L"texture\\M_objectbmp\\팜플렛.bmp"));
	AddObject(paper, EOBJ_TYPE::TEXT);

	CObj* window1 = new CText;
	window1->SetPos(Vec2(64 * 3 + 32, 64 * 6));
	window1->SetScale(Vec2(90, 90));
	if (CStageMgr::GetInst()->IsMuseumEventOn())
		window1->SetUIScript(L"잠겨있지 않은데 열리지 않아...");
	else
		window1->SetUIScript(L" 창밖은 밝다...");
	window1->SetTexture(CResMgr::GetInst()->LoadTexture(L"window", L"texture\\M_objectbmp\\창문.bmp"));
	AddObject(window1, EOBJ_TYPE::TEXT);

	window2 = new CText;
	window2->SetPos(Vec2(64 * 6 + 32, 64 * 6));
	window2->SetScale(Vec2(90, 90));
	if (CStageMgr::GetInst()->IsMuseumEventOn())
		window2->SetUIScript(L"창밖으로 붉은 액체가 흘러내린다...");
	else
		window2->SetUIScript(L" 창밖은 밝다...");

	if(CStageMgr::GetInst()->IsWindow1Played())
		window2->SetTexture(CResMgr::GetInst()->LoadTexture(L"window01_played", L"texture\\M_objectbmp\\window01_played.bmp"));
	else
		window2->SetTexture(CResMgr::GetInst()->FindTexture(L"window"));
	AddObject(window2, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsSubCharOff())
	{
		CObj* subC1 = new CText;
		subC1->SetPos(Vec2(64 * 6 + 32, 64 * 7));
		subC1->SetScale(Vec2(30, 60));
		subC1->SetUIScript(L"\"한 대 피워볼까...\"");
		subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"m00_01", L"texture\\bmp_char\\m00_01.bmp"));
		AddObject(subC1, EOBJ_TYPE::TEXT);

		CObj* subC2 = new CText;
		subC2->SetPos(Vec2(64 * 10 + 32, 64 * 7));
		subC2->SetScale(Vec2(30, 60));
		subC2->SetUIScript(L"\"이쪽으로 들어오시면 안됩니다.\"");
		subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"m00_02", L"texture\\bmp_char\\m00_02.bmp"));
		AddObject(subC2, EOBJ_TYPE::TEXT);

		CObj* subC3 = new CText;
		subC3->SetPos(Vec2(64 * 10, 64 * 9));
		subC3->SetScale(Vec2(30, 60));
		subC3->SetUIScript(L"다른 사람들에게 폐를 끼쳐선 안된단다.");
		subC3->SetTexture(CResMgr::GetInst()->LoadTexture(L"m01", L"texture\\bmp_char\\m01.bmp"));
		AddObject(subC3, EOBJ_TYPE::TEXT);

		CObj* subC4 = new CText;
		subC4->SetPos(Vec2(64 * 11, 64 * 9));
		subC4->SetScale(Vec2(30, 60));
		subC4->SetUIScript(L"아빠는 접수인과 이야기하고 있다...");
		subC4->SetTexture(CResMgr::GetInst()->LoadTexture(L"f01", L"texture\\bmp_char\\f01.bmp"));
		AddObject(subC4, EOBJ_TYPE::TEXT);
	}

	

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);
}

void Stage_M_1F_00::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		if(CStageMgr::GetInst()->IsMuseumSearchDone())
			ChangeStage(ESTAGE_TYPE::M_1F_01_02);
		else
			ChangeStage(ESTAGE_TYPE::M_1F_01);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_2F_01);
	}

	if (CStageMgr::GetInst()->IsMuseumEventOn())
	{
		if (pObj->GetPos().x <= 64.f * 7)
		{
			if (CStageMgr::GetInst()->IsWindow1Played() == false)
			{
				window2->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));

				CSound* bloodSound = CResMgr::GetInst()->FindSound(L"blood");
				bloodSound->Play();

				CObj* windowAni = new CPicture;
				windowAni->SetPos(Vec2(64 * 6 + 32, 64 * 6));
				windowAni->SetScale(Vec2(30, 30));
				windowAni->SetTexture(CResMgr::GetInst()->FindTexture(L"window"));
				((CPicture*)windowAni)->PlayAnimation(L"M_WINDOW");
				CStageMgr::GetInst()->TurnOnWindow1();
				AddObject(windowAni, EOBJ_TYPE::PIC);

			}
		}


		if (((CText*)mainGate)->IsScriptOn())
		{
			CSound* doorNotOpen = CResMgr::GetInst()->FindSound(L"door_not_open");
			doorNotOpen->Play();
		}
	}

}

void Stage_M_1F_00::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_M_1F_00::Enter()
{
	if (CStageMgr::GetInst()->GetPrevStageType() != ESTAGE_TYPE::STARTANIMATION)
		CCamera::GetInst()->FadeIn(0.3f);

	if (CStageMgr::GetInst()->IsSubCharOff())
	{
		if (CStageMgr::GetInst()->IsMStageVeilOn() == false && CStageMgr::GetInst()->IsMuseumEventOn() == false)
		{
			// 블링크 효과
			CCamera::GetInst()->TurnOffHalf(0.25);
			CCamera::GetInst()->TurnON(0.1);
			CCamera::GetInst()->TurnOffHalf(0.3);
			CCamera::GetInst()->TurnON(0.1);

			CStageMgr::GetInst()->TurnMuseumEventOn();
		}
	}

	init();
}

void Stage_M_1F_00::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::TEXT);

}
