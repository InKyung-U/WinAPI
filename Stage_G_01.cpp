#include "pch.h"
#include "Stage_G_01.h"

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
#include "CHand.h"
#include "CUI.h"
#include "CPanel.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_G_01::Stage_G_01()
	: m_pGate01(nullptr)
	, m_pDoor01(nullptr)
	, m_pHand1(nullptr)
	, m_pHand2(nullptr)
	, m_pHand3(nullptr)
	, m_pHand4(nullptr)
	, m_pAnt(nullptr)
	, m_fAddTime(0.f)
	, m_sTakePic{}
	, m_sNotTakePic{}
	, m_iScriptNum(1)
	, m_fAlpha(0.2f)
	, m_pSelectBox(nullptr)
	, m_vSelectBoxPos{}
{
	LoadTileFromFile(L"tile\\g_01");

	m_pSelectBox = CResMgr::GetInst()->LoadTexture(L"SelectBox", L"texture\\whiteBox.bmp");

	m_sTakePic = L"가져간다.";
	m_sNotTakePic = L"가져가지 않는다.";
}

Stage_G_01::~Stage_G_01()
{
}

void Stage_G_01::init()
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


	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 14 + 32, 64.f * 4));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	if (CStageMgr::GetInst()->IsHaveGreenKey())
	{
		CObj* DoorText = new CText;
		DoorText->SetPos(Vec2(64.f * 14 + 32, 64.f * 4));
		DoorText->SetScale(Vec2(64.f, 64.f * 2));
		DoorText->SetUIScript(L"초록 열쇠를 사용했다.");
		DoorText->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullTex", L"texture\\nullbmp.bmp"));
		AddObject(DoorText, EOBJ_TYPE::TEXT);
	}
	else
	{
		CObj* DoorText = new CText;
		DoorText->SetPos(Vec2(64.f * 14 + 32, 64.f * 4));
		DoorText->SetScale(Vec2(64.f, 64.f * 2));
		DoorText->SetUIScript(L"문이 잠겨있다..");
		DoorText->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullTex", L"texture\\nullbmp.bmp"));
		AddObject(DoorText, EOBJ_TYPE::TEXT);
	}


	POINT ptResolution = CCore::GetInst()->GetResolution();

	pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::G_02)
		pObj->SetPos(Vec2(64.f * 19, 64.f * 23));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());
	else
	{
		CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
		doorClose->Play();

		pObj->SetPos(Vec2(64.f * 5 + 32, 64.f * 26));

		if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::GAMEOVER)
		{
			CStageMgr::GetInst()->Setbgm(L"Inquiry");
		}
	}

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 20, 64.f * 24));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	wstring str[3] = { L"개미 그림이 걸려있다."
		, L"자세히 보니 떼어낼 수 있을것 같다"
		, L"떼어내시겠습니까?" };
	// 클릭되는 그림
	text1 = new CText;
	text1->SetPos(Vec2(64 * 9 + 32, 64 * 4));
	text1->SetUIScript(L"개미 그림이 걸려있다.");
	text1->SetScriptList(str);
	if (CStageMgr::GetInst()->HaveAntPic() || CStageMgr::GetInst()->IsAntPicPutTile())
	{
		text1->SetScale(Vec2(0, 0));
		text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullBmp", L"texture\\nullbmp.bmp"));
	}
	else
	{
		text1->SetScale(Vec2(20, 100));
		text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_ant", L"texture\\g_bmp\\g_ant.bmp"));
	}
	AddObject(text1, EOBJ_TYPE::TEXT);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 8 + 32 , 64 * 21));
	text2->SetScale(Vec2(20, 100));
	text2->SetUIScript(L"무당벌레 그림이 걸려 있다..");
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_01", L"texture\\g_bmp\\g_01.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 11 + 32, 64 * 21));
	text3->SetScale(Vec2(20, 100));
	text3->SetUIScript(L"꿀벌 그림이 걸려 있다..");
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_02", L"texture\\g_bmp\\g_02.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	CObj* text4 = new CText;
	text4->SetPos(Vec2(64 * 14 + 32, 64 * 21));
	text4->SetScale(Vec2(20, 100));
	text2->SetUIScript(L"무당벌레 그림이 걸려 있다..");
	text4->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_03", L"texture\\g_bmp\\g_03.bmp"));
	AddObject(text4, EOBJ_TYPE::TEXT);

	CObj* text5 = new CText;
	text5->SetPos(Vec2(64 * 17 + 32, 64 * 21));
	text5->SetScale(Vec2(20, 100));
	text5->SetUIScript(L"거미 그림이 걸려 있다..");
	text5->SetTexture(CResMgr::GetInst()->LoadTexture(L"g_04", L"texture\\g_bmp\\g_04.bmp"));
	AddObject(text5, EOBJ_TYPE::TEXT);

	CObj* text6 = new CText;
	text6->SetPos(Vec2(64 * 4 + 32, 64 * 21 + 32));
	text6->SetScale(Vec2(20, 20));
	text6->SetUIScript(L"테두리 를 주의");
	text6->SetTexture(CResMgr::GetInst()->LoadTexture(L"text1", L"texture\\M_objectbmp\\텍스트1.bmp"));
	AddObject(text6, EOBJ_TYPE::TEXT);

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

	if (CStageMgr::GetInst()->IsHandPopUp())
	{
		// Hand
		m_pHand1 = new CHand;
		m_pHand1->SetPos(Vec2(64 * 3 + 32, 64 * 17 + 32));
		AddObject(m_pHand1, EOBJ_TYPE::HAND);

		m_pHand2 = new CHand;
		m_pHand2->SetPos(Vec2(64 * 6 - 32, 64 * 14 + 32));
		((CHand*)m_pHand2)->PlayAnimation(L"G_HANDR_SWING");
		AddObject(m_pHand2, EOBJ_TYPE::HAND);

		m_pHand3 = new CHand;
		m_pHand3->SetPos(Vec2(64 * 3 + 32, 64 * 11 + 32));
		AddObject(m_pHand3, EOBJ_TYPE::HAND);

		m_pHand4 = new CHand;
		m_pHand4->SetPos(Vec2(64 * 4 + 32, 64 * 5 + 32));
		((CHand*)m_pHand4)->PlayAnimation(L"G_HANDUP_SWING");
		AddObject(m_pHand4, EOBJ_TYPE::HAND);
	}
	//ant
	m_pAnt = new CText;
	m_pAnt->SetPos(Vec2(64 * 13, 64 * 24));
	m_pAnt->SetScale(Vec2(10, 10));
	if (CStageMgr::GetInst()->returnAntPicCount() == 0 && CStageMgr::GetInst()->IsAntPicPutTile())
	{
		m_pAnt->SetUIScript(L"내 그림 어쨌어.");
	}
	else
		m_pAnt->SetUIScript(L"안녕. \n나 개미. \n내 그림 보고 싶은데 좀 멀리 있어.");
	m_pAnt->SetTexture(CResMgr::GetInst()->LoadTexture(L"ant", L"texture\\g_bmp\\ant.bmp"));
	AddObject(m_pAnt, EOBJ_TYPE::TEXT);

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::HAND);

}

void Stage_G_01::update()
{
	if (CStageMgr::GetInst()->GetRoseCount() <= 0)
	{
		CStageMgr::GetInst()->SetRoseCount(5);
		ChangeStage(ESTAGE_TYPE::GAMEOVER);
	}

	CStage::update();
	m_fAddTime += DS;

	CSound* Monster1 = CResMgr::GetInst()->FindSound(L"monster1");
	CSound* Monster2 = CResMgr::GetInst()->FindSound(L"monster2");
	CSound* Monster3 = CResMgr::GetInst()->FindSound(L"monster3");
	CSound* Monster4 = CResMgr::GetInst()->FindSound(L"monster4");

	if (CStageMgr::GetInst()->HaveAntPic())
	{
		text1->SetScale(Vec2(0, 0));
		text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullBmp", L"texture\\nullbmp.bmp"));

		wstring str[3] = { L"우와 내 그림 멋져"
		, L"헤벌레~"
		, L"" };
		m_pAnt->SetScriptList(str);
	}
	else if (CStageMgr::GetInst()->returnAntPicCount() == 0)
	{
		wstring str[3] = { L"내 그림 어쨌어."
				, L""
				, L"" };
		m_pAnt->SetScriptList(str);
	}

	if (1 <= m_fAddTime)
	{
		if (rand() % 2 == 1)
		{
			m_pAnt->AddPos(Vec2(-16, 0));
		}
		else
		{
			m_pAnt->AddPos(Vec2(16, 0));
		}
		m_fAddTime -= 2.f;
	}

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::G_02);
	}

	if (CStageMgr::GetInst()->IsGreenDoorOpen())
	{
		if (KTAP(KEY::UP))
		{
			CSound* doorOpen = CResMgr::GetInst()->FindSound(L"door_open");
			doorOpen->Play();
			((CPlayer*)pObj)->stopFootSound();
			ChangeStage(ESTAGE_TYPE::ENDSTAGE);

		}
	}

	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			if (CStageMgr::GetInst()->IsHaveGreenKey())
			{
				//ChangeStage(ESTAGE_TYPE::Y_04);

				CSound* useKey = CResMgr::GetInst()->FindSound(L"key");
				useKey->Play();
				CStageMgr::GetInst()->OpenGreenDoor();
				CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);
				CStageMgr::GetInst()->TurnOffGreenKey();
			}		
			else 
			{
				CSound* doorNotOpen = CResMgr::GetInst()->FindSound(L"door_not_open");
				doorNotOpen->Play();
			}
		}
	}

	if (CStageMgr::GetInst()->IsHandPopUp() == false)
	{	
		if (64 * 17 + 32 >= pObj->GetPos().y - 32)
		{
			if (m_pHand1 == nullptr)
			{
				Monster1->Play();

				m_pHand1 = new CHand;
				m_pHand1->SetPos(Vec2(64 * 3 + 32, 64 * 17 + 32));
				((CHand*)m_pHand1)->PlayAnimation(L"G_HANDLEFT_POPUP");
				AddObject(m_pHand1, EOBJ_TYPE::HAND);
			}
		}

		if (64 * 14 + 32 >= pObj->GetPos().y - 32) {
			if (m_pHand2 == nullptr)
			{
				Monster2->Play();

				m_pHand2 = new CHand;
				m_pHand2->SetPos(Vec2(64 * 6 - 32, 64 * 14 + 32));
				((CHand*)m_pHand2)->PlayAnimation(L"G_HANDRIGHT_POPUP");
				AddObject(m_pHand2, EOBJ_TYPE::HAND);
			}
		}

		if (64 * 11 + 32 >= pObj->GetPos().y - 32) {
			if (m_pHand3 == nullptr) 
			{
				Monster3->Play();

				m_pHand3 = new CHand;
				m_pHand3->SetPos(Vec2(64 * 3 + 32, 64 * 11 + 32));
				((CHand*)m_pHand3)->PlayAnimation(L"G_HANDLEFT_POPUP");
				AddObject(m_pHand3, EOBJ_TYPE::HAND);
			}
		}

		if (64 * 6 + 32 >= pObj->GetPos().y - 32) {
			if (m_pHand4 == nullptr) 
			{
				Monster4->Play();

				m_pHand4 = new CHand;
				m_pHand4->SetPos(Vec2(64 * 4 + 32, 64 * 5 + 32));
				m_pHand4->SetScale(Vec2(40.f, 80.f));
				((CHand*)m_pHand4)->PlayAnimation(L"G_HANDUP_POPUP");
				AddObject(m_pHand4, EOBJ_TYPE::HAND);
				CStageMgr::GetInst()->TurnOnHandPopUp();
			}

		}
	}

	CSound* select = CResMgr::GetInst()->FindSound(L"select");

	if (CStageMgr::GetInst()->HaveAntPic() == false)
	{
		if (((CText*)text1)->GetScriptCount() == 3)
		{
			m_fAddTime += DS;

			if (0.6f <= m_fAddTime)
			{
				if (m_fAlpha == 0.f)
					m_fAlpha = 0.2f;
				else
					m_fAlpha = 0.f;

				m_fAddTime = 0;
			}

			if (m_iScriptNum == 2)
			{
				if (KTAP(KEY::SPACE))
				{
					CStageMgr::GetInst()->TurnOnAntPic();
					text1->SetScale(Vec2(0, 0));
					text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullBmp", L"texture\\nullbmp.bmp"));
				}
			}
			else
			{
				if (KTAP(KEY::SPACE))
					select->Play();
			}
			

			if (KTAP(KEY::UP))
			{
				if (m_iScriptNum == 1)
					m_iScriptNum = 1;
				else if (m_iScriptNum == 2)
				{
					select->Play();
					m_iScriptNum = 1;
				}
			}
			if (KTAP(KEY::DOWN))
			{
				if (m_iScriptNum == 1)
				{
					select->Play();
					m_iScriptNum = 2;
				}
				else if (m_iScriptNum == 2)
					m_iScriptNum = 2;
			}

			if (m_iScriptNum == 1)
				m_vSelectBoxPos = Vec2(312 + 30, 500 + 50);
			if (m_iScriptNum == 2)
				m_vSelectBoxPos = Vec2(312 + 30, 500 + 50 + 75);
		}
	}

	if (((CText*)text1)->IsScriptSearchDone())
	{
		if (m_iScriptNum == 2)
		{
			if (CStageMgr::GetInst()->HaveAntPic() == false)
			{
				CStageMgr::GetInst()->TurnOnAntPic();
				text1->SetScale(Vec2(0, 0));
				text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullBmp", L"texture\\nullbmp.bmp"));
				CSound* itemGet = CResMgr::GetInst()->FindSound(L"item_get");
				itemGet->Play();
			}
		}

	}
}

void Stage_G_01::render(HDC _dc)
{
	CStage::render(_dc);

	if (CStageMgr::GetInst()->HaveAntPic() == false)
	{
		if (((CText*)text1)->GetScriptCount() == 3)
		{
			BLENDFUNCTION bf = {};
			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = 255 * m_fAlpha;
			bf.AlphaFormat = 0;

			AlphaBlend(_dc
				, m_vSelectBoxPos.x
				, m_vSelectBoxPos.y
				, 340, 65
				, m_pSelectBox->GetDC()
				, 0, 0
				, m_pSelectBox->Width(), m_pSelectBox->Height()
				, bf);

			RECT rectangle1;
			SetRect(&rectangle1, 350, 545 + 20, 350 + 314, 545 + 63 + 20);
			DrawText(_dc, m_sNotTakePic.c_str(), -1, &rectangle1, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL);

			RECT rectangle2;
			SetRect(&rectangle2, 350, 545 + 93, 350 + 314, 545 + 123 + 33);
			DrawText(_dc, m_sTakePic.c_str(), -1, &rectangle2, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL);
		}
	}
}

void Stage_G_01::Enter()
{
	init();

	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_G_01::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::HAND);
	Clear(EOBJ_TYPE::UI);
}
