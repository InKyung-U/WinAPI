#include "pch.h"
#include "Stage_M_2F_02.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CTexture.h"
#include "CText.h"
#include "CPicture.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_M_2F_02::Stage_M_2F_02()
	:m_pGate01(nullptr)
	, m_pGate02(nullptr)
	, m_bCat(false)
{
	LoadTileFromFile(L"tile\\m_2F_02");
}

Stage_M_2F_02::~Stage_M_2F_02()
{
}

void Stage_M_2F_02::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_2F_01)
		pObj->SetPos(Vec2(64.f * 1, 64.f * 11));
	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_pic)
		pObj->SetPos(Vec2(64.f * 1, 64.f * 33));

	//pObj->SetPos(Vec2(64.f, 640.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	// Gate 배치
	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0, 64.f * 11));
	m_pGate01->SetScale(Vec2(64.f * 1, 64.f * 6));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 0, 64.f * 33));
	m_pGate02->SetScale(Vec2(64.f * 1, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// pic
	// 그림
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 3 + 32, 64 * 6 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_05", L"texture\\미술관그림bmp\\2_05.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 7 + 32, 64 * 6 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"redLady", L"texture\\미술관그림bmp\\redLady.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	pic3 = new CPicture;
	pic3->SetPos(Vec2(64 * 11 + 32, 64 * 6 + 32));
	pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_07", L"texture\\미술관그림bmp\\2_07.bmp"));
	AddObject(pic3, EOBJ_TYPE::PIC);

	CObj* pic4 = new CPicture;
	pic4->SetPos(Vec2(64 * 15 + 32, 64 * 6 + 32));
	pic4->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_08", L"texture\\미술관그림bmp\\2_08.bmp"));
	AddObject(pic4, EOBJ_TYPE::PIC);

	CObj* pic5 = new CPicture;
	pic5->SetPos(Vec2(64 * 6 + 32, 64 * 28 + 32));
	pic5->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_09", L"texture\\미술관그림bmp\\2_09.bmp"));
	AddObject(pic5, EOBJ_TYPE::PIC);

	CObj* pic6 = new CPicture;
	pic6->SetPos(Vec2(64 * 2 + 32, 64 * 28 + 32));
	pic6->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_010", L"texture\\미술관그림bmp\\2_010.bmp"));
	AddObject(pic6, EOBJ_TYPE::PIC);

	// 오브젝트
	CObj* obj1 = new CPicture;
	obj1->SetPos(Vec2(64 * 14, 64 * 13));
	obj1->SetTexture(CResMgr::GetInst()->LoadTexture(L"m_02", L"texture\\M_objectbmp\\m_02.bmp"));
	AddObject(obj1, EOBJ_TYPE::PIC);

	CObj* obj2 = new CPicture;
	obj2->SetPos(Vec2(64 * 14, 64 * 21));
	obj2->SetTexture(CResMgr::GetInst()->LoadTexture(L"m_03", L"texture\\M_objectbmp\\m_03.bmp"));
	AddObject(obj2, EOBJ_TYPE::PIC);

	CObj* obj3 = new CPicture;
	obj3->SetPos(Vec2(64 * 14, 64 * 29));
	obj3->SetTexture(CResMgr::GetInst()->LoadTexture(L"m_01", L"texture\\M_objectbmp\\m_01.bmp"));
	AddObject(obj3, EOBJ_TYPE::PIC);

	// 텍스트
	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 3 + 32, 64 * 7 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetUIScript(L"\'?? 없는 다이아몬드\'\n어려워서 읽을 수 없는 글자가 있다...");
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 7 + 32, 64 * 7 + 32));
	text2->SetScale(Vec2(20, 20));
	text2->SetUIScript(L"\'붉은 옷의 여인\'\n");
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 11 + 32, 64 * 7 + 32));
	text3->SetScale(Vec2(20, 20));
	text3->SetUIScript(L"\'쓰디쓴 과실\'\n");
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	CObj* text4 = new CText;
	text4->SetPos(Vec2(64 * 15 + 32, 64 * 7 + 32));
	text4->SetScale(Vec2(20, 20));
	text4->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text4, EOBJ_TYPE::TEXT);

	CObj* text5 = new CText;
	text5->SetPos(Vec2(64 * 6 + 32, 64 * 29 + 32));
	text5->SetScale(Vec2(20, 20));
	text5->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text5, EOBJ_TYPE::TEXT);

	CObj* text6 = new CText;
	text6->SetPos(Vec2(64 * 2 + 32, 64 * 29 + 32));
	text6->SetScale(Vec2(20, 20));
	text6->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text6, EOBJ_TYPE::TEXT);

	CObj* standText1 = new CText;
	standText1->SetPos(Vec2(64 * 14, 64 * 16 + 32));
	standText1->SetScale(Vec2(20, 20));
	standText1->SetTexture(CResMgr::GetInst()->LoadTexture(L"설명1", L"texture\\M_objectbmp\\설명1.bmp"));
	AddObject(standText1, EOBJ_TYPE::TEXT);

	CObj* standText2 = new CText;
	standText2->SetPos(Vec2(64 * 14, 64 * 24 + 32));
	standText2->SetScale(Vec2(20, 20));
	standText2->SetTexture(CResMgr::GetInst()->LoadTexture(L"설명1", L"texture\\M_objectbmp\\설명1.bmp"));
	AddObject(standText2, EOBJ_TYPE::TEXT);

	CObj* standText3 = new CText;
	standText3->SetPos(Vec2(64 * 14, 64 * 32 + 32));
	standText3->SetScale(Vec2(20, 20));
	standText3->SetTexture(CResMgr::GetInst()->LoadTexture(L"설명1", L"texture\\M_objectbmp\\설명1.bmp"));
	AddObject(standText3, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsSubCharOff())
	{
		CObj* subC1 = new CText;
		subC1->SetPos(Vec2(64 * 7 + 32, 64 * 8 + 32));
		subC1->SetScale(Vec2(30, 60));
		subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m02_01", L"texture\\bmp_char\\2m02_01.bmp"));
		AddObject(subC1, EOBJ_TYPE::TEXT);

		CObj* subC2 = new CText;
		subC2->SetPos(Vec2(64 * 14 +32, 64 * 16 + 32));
		subC2->SetScale(Vec2(30, 60));
		subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m02_03", L"texture\\bmp_char\\2m02_03.bmp"));
		AddObject(subC2, EOBJ_TYPE::TEXT);

		CObj* subC3 = new CText;
		subC3->SetPos(Vec2(64 * 15 + 32, 64 * 8 + 32));
		subC3->SetScale(Vec2(30, 60));
		subC3->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m02_02", L"texture\\bmp_char\\2m02_02.bmp"));
		AddObject(subC3, EOBJ_TYPE::TEXT);

		CObj* subC4 = new CText;
		subC4->SetPos(Vec2(64 * 15, 64 * 27 + 20));
		subC4->SetScale(Vec2(30, 60));
		subC4->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m02_04", L"texture\\bmp_char\\2m02_04.bmp"));
		AddObject(subC4, EOBJ_TYPE::TEXT);

		CObj* subC5 = new CText;
		subC5->SetPos(Vec2(64 * 12, 64 * 21 + 32));
		subC5->SetScale(Vec2(30, 60));
		subC5->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m02_05", L"texture\\bmp_char\\2m02_05.bmp"));
		AddObject(subC5, EOBJ_TYPE::TEXT);

		CObj* subC6 = new CText;
		subC6->SetPos(Vec2(64 * 6 + 32, 64 * 30 + 15));
		subC6->SetScale(Vec2(30, 60));
		subC6->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m02_06", L"texture\\bmp_char\\2m02_06.bmp"));
		AddObject(subC6, EOBJ_TYPE::TEXT);
	}

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_M_2F_02::update()
{

	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_2F_01);
	}
	if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_pic);
	}

	if (CStageMgr::GetInst()->IsMuseumEventOn())
	{
		if (pObj->GetPos().y < 64.f * 12)
		{
			m_fAddTime += DS;
			if (CStageMgr::GetInst()->IsRedBallPlayed() == false)
			{
				((CPicture*)pic3)->PlayAnimation(L"M_PIC_REDBALL");
				CStageMgr::GetInst()->TurnOnRedBall();
			}
			else if (0.3f < m_fAddTime)
			{
				if (100.f <= m_fAddTime)
				{

				}
				else
				{
					CSound* ball = CResMgr::GetInst()->FindSound(L"RedBall");
					ball->Play();

					((CPicture*)pic3)->PlayAnimation(L"REDBALL_PIC");
					CObj* pic_ball = new CPicture;
					pic_ball->SetPos(Vec2(64 * 11 + 32, 64 * 8 + 32));
					((CPicture*)pic_ball)->PlayAnimation(L"M_BALL_FALL");
					pic_ball->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));
					AddObject(pic_ball, EOBJ_TYPE::PIC);

					m_fAddTime = 100.f;
				}
			}
		}

		if (m_bCat == false)
		{
			Vec2 playerPos = CStageMgr::GetInst()->GetPlayer()->GetPos();

			if (64 * 26 < playerPos.y)
			{
				CSound* cat = CResMgr::GetInst()->FindSound(L"cat");
				cat->Play();
				m_bCat = true;						
			}
		}
	}

}

void Stage_M_2F_02::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_M_2F_02::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_M_2F_02::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);

}
