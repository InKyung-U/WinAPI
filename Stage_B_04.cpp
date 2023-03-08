#include "pch.h"
#include "Stage_B_04.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"
#include "CPicture.h"
#include "CText.h"
#include "CTable.h"
#include "CUI.h"
#include "CPanel.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_B_04::Stage_B_04()
	: m_pGate01(nullptr)
	, m_pDoor01(nullptr)
	, m_pObj(nullptr)
	, m_pRose(nullptr)
	, m_fAddTime(0.f)
	, m_pText1(nullptr)
	, m_pText2(nullptr)
	, m_pText3(nullptr)
{
	LoadTileFromFile(L"tile\\b_04");
}

Stage_B_04::~Stage_B_04()
{
}

void Stage_B_04::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	m_pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::B_03)
	{
		CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
		doorClose->Play();
		m_pObj->SetPos(Vec2(64.f * 24 + 32, 64.f * 7));
	}
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		m_pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());
	else 
		m_pObj->SetPos(Vec2(64.f * 1, 64.f * 9));

	m_pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(m_pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(m_pObj->GetPos());
	StageAdjustment();

	// gate
	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0, 64.f * 9));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// door
	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 24 + 32, 64.f * 6));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 1));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);

	// 물병테이블
	// 물병은 일단 텍스트로 해놓고 장미 사라지면 테이블로 해놓자
	if (CStageMgr::GetInst()->IsPlayerHaveRose() == false)
	{
		wstring str[3] = { L"장미꽃이 있다.", L"장미꽃을 얻었다.",L"" };

		rose = new CText;
		rose->SetPos(Vec2(64 * 24 + 32, 64 * 7 + 32));
		rose->SetScale(Vec2(100, 40));
		rose->SetScriptList(str);
		rose->SetTexture(CResMgr::GetInst()->LoadTexture(L"장미물병", L"texture\\장미물병테이블.bmp"));
		AddObject(rose, EOBJ_TYPE::TEXT);
		CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);


		m_pRose = new CTable;
		m_pRose->SetPos(Vec2(64 * 24 + 32, 64 * 7 + 32));
		m_pRose->SetScale(Vec2(70, 40));
		m_pRose->SetTexture(CResMgr::GetInst()->LoadTexture(L"장미물병", L"texture\\장미물병테이블.bmp"));
		AddObject(m_pRose, EOBJ_TYPE::TABLE);
		CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TABLE);
	}
	else
	{
		m_pRose = new CTable;
		if (CStageMgr::GetInst()->GetTablePos() == Vec2(0, 0))
		{
			m_pRose->SetPos(Vec2(64 * 24 + 32, 64 * 7 + 32));
			CStageMgr::GetInst()->SetTablePos(m_pRose->GetPos());
		}
		else
			m_pRose->SetPos(CStageMgr::GetInst()->GetTablePos());
		m_pRose->SetScale(Vec2(90, 40));
		m_pRose->SetTexture(CResMgr::GetInst()->LoadTexture(L"물병", L"texture\\물병테이블.bmp"));
		AddObject(m_pRose, EOBJ_TYPE::TABLE);
		CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TABLE);
	}

	// 그림
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 4 + 32, 64 * 4 + 32));
	if(CStageMgr::GetInst()->IsHaveBlueKey())
		pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"돌", L"texture\\b_bmp\\b_돌.bmp"));
	else
		pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"이", L"texture\\b_bmp\\b_이.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);
	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 6 + 32, 64 * 6 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"려", L"texture\\b_bmp\\b_려.bmp"));
	else
		pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"리", L"texture\\b_bmp\\b_리.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);
	CObj* pic3 = new CPicture;
	pic3->SetPos(Vec2(64 * 9 + 32, 64 * 5 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"줘", L"texture\\b_bmp\\b_줘.bmp"));
	else
		pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"온", L"texture\\b_bmp\\b_온.bmp"));
	AddObject(pic3, EOBJ_TYPE::PIC);

	CObj* pic1_1 = new CPicture;
	pic1_1->SetPos(Vec2(64 * 13 + 32, 64 * 2 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic1_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"돌", L"texture\\b_bmp\\b_돌.bmp"));
	else
		pic1_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"이", L"texture\\b_bmp\\b_이.bmp"));
	AddObject(pic1_1, EOBJ_TYPE::PIC);
	CObj* pic2_1 = new CPicture;
	pic2_1->SetPos(Vec2(64 * 14 + 32, 64 * 6 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic2_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"려", L"texture\\b_bmp\\b_려.bmp"));
	else
		pic2_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"리", L"texture\\b_bmp\\b_리.bmp"));
	AddObject(pic2_1, EOBJ_TYPE::PIC);
	CObj* pic3_1 = new CPicture;
	pic3_1->SetPos(Vec2(64 * 17 + 32, 64 * 3 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic3_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"줘", L"texture\\b_bmp\\b_줘.bmp"));
	else
		pic3_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"온", L"texture\\b_bmp\\b_온.bmp"));
	AddObject(pic3_1, EOBJ_TYPE::PIC);

	CObj* pic1_2 = new CPicture;
	pic1_2->SetPos(Vec2(64 * 20 + 32, 64 * 5 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic1_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"돌", L"texture\\b_bmp\\b_돌.bmp"));
	else
		pic1_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"이", L"texture\\b_bmp\\b_이.bmp"));
	AddObject(pic1_2, EOBJ_TYPE::PIC);
	CObj* pic2_2 = new CPicture;
	pic2_2->SetPos(Vec2(64 * 23 + 32, 64 * 2 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic2_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"려", L"texture\\b_bmp\\b_려.bmp"));
	else
		pic2_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"리", L"texture\\b_bmp\\b_리.bmp"));
	AddObject(pic2_2, EOBJ_TYPE::PIC);
	CObj* pic3_2 = new CPicture;
	pic3_2->SetPos(Vec2(64 * 25 + 32, 64 * 3 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic3_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"줘", L"texture\\b_bmp\\b_줘.bmp"));
	else
		pic3_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"온", L"texture\\b_bmp\\b_온.bmp"));
	AddObject(pic3_2, EOBJ_TYPE::PIC);

	CObj* pic1_3 = new CPicture;
	pic1_3->SetPos(Vec2(64 * 27 + 32, 64 * 4 + 32));
	if (CStageMgr::GetInst()->IsHaveBlueKey())
		pic1_3->SetTexture(CResMgr::GetInst()->LoadTexture(L"돌", L"texture\\b_bmp\\b_돌.bmp"));
	else
		pic1_3->SetTexture(CResMgr::GetInst()->LoadTexture(L"이", L"texture\\b_bmp\\b_이.bmp"));
	AddObject(pic1_3, EOBJ_TYPE::PIC);

}

void Stage_B_04::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::B_00);
	}

	Vec2 vPos = m_pObj->GetPos();

	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CSound* doorEnter = CResMgr::GetInst()->FindSound(L"door_open");
			doorEnter->Play();
			ChangeStage(ESTAGE_TYPE::B_03);
		}
	}

	if (((CText*)rose)->IsScriptSearchDone() && CStageMgr::GetInst()->IsPlayerHaveRose() == false)
	{
		rose->SetPos(Vec2(0,0));
		rose->SetScale(Vec2(0, 0));
		rose->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));
		m_pRose->SetTexture(CResMgr::GetInst()->LoadTexture(L"물병", L"texture\\물병테이블.bmp"));
		m_pRose->SetPos(m_pRose->GetPos() + Vec2(0, 10));
		CStageMgr::GetInst()->SetRoseTurnTrue();
		CSound* roseGet = CResMgr::GetInst()->FindSound(L"item_get");
		roseGet->Play();
	}

	if (((CTable*)m_pRose)->GetTableMove())
	{
		//if (KTAP(KEY::SPACE) && CStageMgr::GetInst()->IsPlayerHaveRose() == false)
		//{
		//	rose->SetScale(Vec2(0, 0));
		//	rose->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));
		//	m_pRose->SetTexture(CResMgr::GetInst()->LoadTexture(L"물병", L"texture\\물병테이블.bmp"));
		//	m_pRose->SetPos(m_pRose->GetPos() + Vec2(0, 10));
		//	CStageMgr::GetInst()->SetRoseTurnTrue();
		//	CSound* roseGet = CResMgr::GetInst()->FindSound(L"item_get");
		//	roseGet->Play();
		//}

		if (KTAP(KEY::RIGHT))
		{
			if (CStageMgr::GetInst()->IsPlayerHaveRose())
			{
				if (m_pObj->GetPos().x < m_pRose->GetPos().x)
				{
					CSound* table = CResMgr::GetInst()->FindSound(L"table_move");
					table->Play();
					((CTable*)m_pRose)->SetMovingTableOn(Vec2(0.5f, 0.f));
				}
			}
		}
		else if (KTAP(KEY::LEFT))
		{
			if (CStageMgr::GetInst()->IsPlayerHaveRose())
			{
				if (m_pObj->GetPos().x > m_pRose->GetPos().x)
				{
					CSound* table = CResMgr::GetInst()->FindSound(L"table_move");
					table->Play();
					((CTable*)m_pRose)->SetMovingTableOn(Vec2(-0.5f, 0.f));
				}
			}
		}
	}

	CSound* word = CResMgr::GetInst()->FindSound(L"Word");
	if (CStageMgr::GetInst()->IsHaveBlueKey())
	{
		if (m_pObj->GetPos().x <= 64.f * 11)
		{
			m_fAddTime += DS;

			if (m_pText1 == nullptr)
			{
				word->Play();

				m_pText1 = new CPicture;
				m_pText1->SetPos(Vec2(64 * 4 + 32, 64 * 8 + 32));
				m_pText1->SetTexture(CResMgr::GetInst()->LoadTexture(L"돌", L"texture\\b_bmp\\b_돌.bmp"));
				AddObject(m_pText1, EOBJ_TYPE::PIC);
			}

			if (m_pText2 == nullptr && 0.5f <= m_fAddTime)
			{
				word->Play();

				m_pText2 = new CPicture;
				m_pText2->SetPos(Vec2(64 * 6 + 32, 64 * 9 + 32));
				m_pText2->SetTexture(CResMgr::GetInst()->LoadTexture(L"려", L"texture\\b_bmp\\b_려.bmp"));
				AddObject(m_pText2, EOBJ_TYPE::PIC);
			}

			if (m_pText3 == nullptr && 1.f <= m_fAddTime)
			{
				word->Play();

				m_pText3 = new CPicture;
				m_pText3->SetPos(Vec2(64 * 9 + 32, 64 * 10 + 32));
				m_pText3->SetTexture(CResMgr::GetInst()->LoadTexture(L"줘", L"texture\\b_bmp\\b_줘.bmp"));
				AddObject(m_pText3, EOBJ_TYPE::PIC);
			}
		}
	}

}

void Stage_B_04::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_B_04::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_B_04::Exit()
{

	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::TABLE);
	Clear(EOBJ_TYPE::SCRIPTUI);

}
