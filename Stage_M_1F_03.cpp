#include "pch.h"
#include "Stage_M_1F_03.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CText.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_M_1F_03::Stage_M_1F_03()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
	, m_pic2(nullptr)
	, m_fAddTime(0.f)
{
	LoadTileFromFile(L"tile\\m_1F_03");
}

Stage_M_1F_03::~Stage_M_1F_03()
{
}

void Stage_M_1F_03::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_01)
		pObj->SetPos(Vec2(64.f * 11, 64.f * 2));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_01_02)
		pObj->SetPos(Vec2(64.f * 11, 64.f * 2));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_02)
		pObj->SetPos(Vec2(64.f * 18, 64.f * 10));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 10, 64.f * 0));
	m_pGate01->SetScale(Vec2(64.f * 6, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 19, 64.f * 10));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// 오브젝트
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 3 + 32, 64 * 8 ));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"rose", L"texture\\M_objectbmp\\m_04.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	wstring str[3] = { L"\'정신의 ???\n그 모습은 보기에 아릅다지만\n지나치게 가까이 가면 아픈 꼴을 ? 한다\n??한 육체밖에는 피지 않는다\'"
		, L"어려워서 읽을 수 없는 글자가 있다...", L"" };
	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 6 + 32, 64 * 6));
	text1->SetScale(Vec2(50, 50));
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"텍스트1", L"texture\\M_objectbmp\\텍스트1.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	m_pic2 = new CPicture;
	m_pic2->SetPos(Vec2(64 * 15 + 32, 64 * 5 + 32));
	m_pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_07", L"texture\\미술관그림bmp\\1_07.bmp"));
	AddObject(m_pic2, EOBJ_TYPE::PIC);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 15 + 32, 64 * 6 + 32));
	text2->SetScale(Vec2(20, 20));
	text2->SetUIScript(L"\'기침하는 남자\'");
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsSubCharOff())
	{
		CObj* subC1 = new CText;
		subC1->SetPos(Vec2(64 * 6 + 32, 64 * 10));
		subC1->SetScale(Vec2(30, 60));
		subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m03_01", L"texture\\bmp_char\\1m03_01.bmp"));
		AddObject(subC1, EOBJ_TYPE::TEXT);

	}

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_M_1F_03::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		if (CStageMgr::GetInst()->IsMuseumSearchDone())
			ChangeStage(ESTAGE_TYPE::M_1F_01_02);
		else
			ChangeStage(ESTAGE_TYPE::M_1F_01);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_02);
	}

}

void Stage_M_1F_03::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_M_1F_03::Enter()
{
	init();

	if (CStageMgr::GetInst()->IsMuseumEventOn())
	{
		m_fAddTime += DS;
		if (1.f < m_fAddTime)
		{
			CSound* sneeze = CResMgr::GetInst()->FindSound(L"sneeze");
			sneeze->Play();
			if (100.f <= m_fAddTime)
			{
				m_fAddTime = 101.f;
			}
		}
		((CPicture*)m_pic2)->PlayAnimation(L"M_SNEEZE_MAN");
	}

	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_M_1F_03::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
}

