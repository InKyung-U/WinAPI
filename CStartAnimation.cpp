#include "pch.h"
#include "CStartAnimation.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"
#include "CUIMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CTexture.h"
#include "CPicture.h"
#include "CText.h"
#include "CScript.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CStartAnimation::CStartAnimation()
	: m_pPlayer(nullptr)
	, m_pMather(nullptr)
	, m_pFather(nullptr)
	, m_pScript{}
	, m_fAddTime(0.f)
	, m_stageScript1_On(false)
	, m_stageScript2_On(false)
	, m_stageScript3_On(false)
	, m_iScriptCount(0)
{
	LoadTileFromFile(L"tile\\m_1F_00");
}

CStartAnimation::~CStartAnimation()
{
}

void CStartAnimation::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	//CObj* pObj = new CPlayer;
	//pObj->SetPos(Vec2(64.f, 640.f));

	// 오브젝트
	CObj* window = new CPicture;
	window->SetPos(Vec2(64 * 10 + 32, 64 * 4 + 32));
	window->SetTexture(CResMgr::GetInst()->LoadTexture(L"poster", L"texture\\M_objectbmp\\포스터.bmp"));
	AddObject(window, EOBJ_TYPE::PIC);

	CObj* table = new CPicture;
	table->SetPos(Vec2(64 * 10 + 32, 64 * 8 + 20));
	table->SetTexture(CResMgr::GetInst()->LoadTexture(L"table", L"texture\\M_objectbmp\\탁자.bmp"));
	AddObject(table, EOBJ_TYPE::PIC);

	CObj* paper = new CPicture;
	paper->SetPos(Vec2(64 * 8 + 32, 64 * 8 + 30));
	paper->SetTexture(CResMgr::GetInst()->LoadTexture(L"paper", L"texture\\M_objectbmp\\팜플렛.bmp"));
	AddObject(paper, EOBJ_TYPE::PIC);

	CObj* window1 = new CText;
	window1->SetPos(Vec2(64 * 3 + 32, 64 * 6));
	window1->SetTexture(CResMgr::GetInst()->LoadTexture(L"window", L"texture\\M_objectbmp\\창문.bmp"));
	AddObject(window1, EOBJ_TYPE::TEXT);

	CObj* window2 = new CText;
	window2->SetPos(Vec2(64 * 6 + 32, 64 * 6));
	window2->SetTexture(CResMgr::GetInst()->FindTexture(L"window"));
	AddObject(window2, EOBJ_TYPE::TEXT);

	
	CObj* subC1 = new CText;
	subC1->SetPos(Vec2(64 * 6 + 32, 64 * 7));
	subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"m00_01", L"texture\\bmp_char\\m00_01.bmp"));
	AddObject(subC1, EOBJ_TYPE::TEXT);

	CObj* subC2 = new CText;
	subC2->SetPos(Vec2(64 * 10 + 32, 64 * 7));
	subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"m00_02", L"texture\\bmp_char\\m00_02.bmp"));
	AddObject(subC2, EOBJ_TYPE::TEXT);


	m_pFather = new CPicture;
	m_pFather->SetPos(Vec2(64 * 0, 64 * 9));
	((CPicture*)m_pFather)->PlayAnimation(L"DAD_WALKR");
	m_pFather->SetTexture(CResMgr::GetInst()->LoadTexture(L"f01_nulltex", L"texture\\nullbmp.bmp"));
	AddObject(m_pFather, EOBJ_TYPE::PIC);

	m_pMather = new CPicture;
	m_pMather->SetPos(Vec2(64 * 0, 64 * 10));
	((CPicture*)m_pMather)->PlayAnimation(L"MOM_WALKR");
	m_pMather->SetTexture(CResMgr::GetInst()->LoadTexture(L"m01_nulltex", L"texture\\nullbmp.bmp"));
	AddObject(m_pMather, EOBJ_TYPE::PIC);

	m_pPlayer = new CPicture;
	m_pPlayer->SetPos(Vec2(64 * 0, 64 * 11));
	((CPicture*)m_pPlayer)->PlayAnimation(L"WALKRIGHT_IB");
	m_pPlayer->SetTexture(CResMgr::GetInst()->LoadTexture(L"ib_startAnimation", L"texture\\nullbmp.bmp"));
	AddObject(m_pPlayer, EOBJ_TYPE::PIC);

	m_pPlayer->SetScale(Vec2(100.f, 100.f));

	CCamera::GetInst()->SetLookAtPos(Vec2(64.f * 9, 64.f * 9));
	StageAdjustment();
}

void CStartAnimation::update()
{
	CStage::update();

	if (m_stageScript3_On == true)
	{
		if (KTAP(KEY::SPACE))
		{
			++m_iScriptCount;
		}
		CUIMgr::GetInst()->ScriptTurnOn();
		if (m_iScriptCount == 0)
			m_pScript->SetUIScript(L"\"응? 먼저 가서 보고 싶다고? \n이브도 참.. 어쩔 수 없구나\"");
		if (m_iScriptCount == 1)
			m_pScript->SetUIScript(L"\"알겠니? 미술관에서는  \n조용히 있어야 한단다?\"");
		if (m_iScriptCount == 2)
		{
			m_pScript->SetUIScript(L"\"...뭐 이브라면  \n걱정 없을 거라고 생각하지만\"");
		}
		if (m_iScriptCount == 3)
		{
			m_pScript->SetUIScript(L"\"다른 사람들에게 폐를 끼쳐선 \n안된단다\"");
		}
		if (m_iScriptCount == 4)
		{
			CUIMgr::GetInst()->ScriptTurnOff();
			ChangeStage(ESTAGE_TYPE::M_1F_00);
		}
	}
	else if (m_stageScript2_On == true)
	{
		m_fAddTime += DS;
		if (0.8f < m_fAddTime)
			((CPicture*)m_pPlayer)->PlayAnimation(L"WALKRIGHT_IB");
		if (1.f < m_fAddTime)
		{
			if (m_pPlayer->GetPos().x < 64.f * 9)
			{
				m_pPlayer->AddPos(Vec2((UINT)(200 * DS), 0));
			}
			else if (m_pPlayer->GetPos().y > 64.f * 9)
			{
				((CPicture*)m_pPlayer)->PlayAnimation(L"STANDUP_IB");
				m_pPlayer->AddPos(Vec2(0, (UINT)(-200 * DS)));
			}
			else
			{
				((CPicture*)m_pPlayer)->PlayAnimation(L"STANDUP_IB");
			}
			if (5.5f < m_fAddTime)
			{
				((CPicture*)m_pPlayer)->PlayAnimation(L"STANDRIGHT_IB");
			}
			if (7.5f < m_fAddTime)
			{
				m_stageScript3_On = true;
				m_fAddTime = 0;
				m_iScriptCount = 0;
			}
		}


		if (m_pMather->GetPos().x < 64.f * 10)
		{
			m_pMather->AddPos(Vec2((UINT)(200 * DS),0));
		}
		else if (m_pMather->GetPos().y > 64.f * 9)
		{
			((CPicture*)m_pMather)->PlayAnimation(L"MOM_STANDUP");
			m_pMather->AddPos(Vec2(0, (UINT)(-200 * DS)));
		}


		if (m_pFather->GetPos().x < 64.f * 11)
		{
			m_pFather->AddPos(Vec2((UINT)(200 * DS), 0));
		}
		else if (m_pFather->GetPos().y >= 64.f * 9)
		{
			((CPicture*)m_pFather)->PlayAnimation(L"DAD_STANDUP");
			m_pFather->AddPos(Vec2(0, (UINT)(-200 * DS)));
		}
	}
	else if (m_stageScript1_On == false)
	{
		if (m_fAddTime < 1.5f)
		{
			m_fAddTime += DS;
			m_pPlayer->AddPos(Vec2(2, 0));
			m_pMather->AddPos(Vec2(1, 0));
			m_pFather->AddPos(Vec2(1, 0));
		}
		else if (m_fAddTime < 3.f)
		{
			m_fAddTime += DS;
			((CPicture*)m_pPlayer)->PlayAnimation(L"STANDRIGHT_IB");
			m_pMather->AddPos(Vec2(1, 0));
			m_pFather->AddPos(Vec2(1, 0));
		}
		else
		{
			((CPicture*)m_pFather)->PlayAnimation(L"DAD_STANDR");
			((CPicture*)m_pMather)->PlayAnimation(L"MOM_STANDD");
			((CPicture*)m_pPlayer)->PlayAnimation(L"STANDUP_IB");
	

			m_pScript = new CScript;
			m_pScript->SetUIScript(L"\"자, 도착했다. \n...이브는 미술관이 처음이지?\"");
			CStageMgr::GetInst()->GetCurStage()->AddObject(m_pScript, EOBJ_TYPE::SCRIPTUI);
			CUIMgr::GetInst()->ScriptTurnOn();
			m_stageScript1_On = true;
			m_fAddTime = 0.f;
			
		}
	}
	else
	{
		if (KTAP(KEY::SPACE))
		{
			++m_iScriptCount;
		}

		if(m_iScriptCount == 1)
			m_pScript->SetUIScript(L"\"오늘 보러 온 건 \n\'게르테나\'라는 사람의 \n전람회인데...\"");
		if (m_iScriptCount == 2)
			m_pScript->SetUIScript(L"\"그림 말고도 조각이라던지.. \n여러 가지 재미있는 작품이 있으니까\"");
		if (m_iScriptCount == 3)
		{
			m_pScript->SetUIScript(L"\"분명 이브에게도 \n재밌을거라고 생각해\"");
		}
		if (m_iScriptCount == 4)
		{
			m_fAddTime += DS;
			if (m_fAddTime < 1.f)
			{
				CUIMgr::GetInst()->ScriptTurnOff();
				m_pScript->SetUIScript(L"");
				((CPicture*)m_pFather)->PlayAnimation(L"DAD_STANDD");
			}
			if (m_fAddTime > 1.f)
			{
				CUIMgr::GetInst()->ScriptTurnOn();
				m_pScript->SetUIScript(L"\"그럼 접수하러 가볼까\"");
			}
		}
		if (m_iScriptCount == 5)
		{
			m_fAddTime = 0;
			m_pScript->SetUIScript(L"\"그렇지 나중에 \n팸플릿도 가져가요\"");
		}
		if (m_iScriptCount == 6)
		{
			m_pScript->SetUIScript(L"");
			CUIMgr::GetInst()->ScriptTurnOff();
			m_stageScript2_On = true;

			((CPicture*)m_pFather)->PlayAnimation(L"DAD_WALKR");
			((CPicture*)m_pMather)->PlayAnimation(L"MOM_WALKR");
		}
	}
}

void CStartAnimation::render(HDC _dc)
{
	CStage::render(_dc);
}

void CStartAnimation::Enter()
{
	CStageMgr::GetInst()->Setbgm(L"museum");

	init();

	CCamera::GetInst()->FadeIn(4.f);
}

void CStartAnimation::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::TEXT);
}

