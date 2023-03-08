#include "pch.h"
#include "CStageMgr.h"

#include "CTitle.h"
#include "CStage_Tool.h"
#include "CStage_Start.h"
#include "CStage_Play01.h"

#include "CStartAnimation.h"
#include "CStartScript.h"
#include "EndStage.h"
#include "GameOver.h"

#include "Stage_M_1F_00.h"
#include "Stage_M_1F_01.h"
#include "Stage_M_1F_01_02.h"
#include "Stage_M_1F_02.h"
#include "Stage_M_1F_03.h"
#include "Stage_M_2F_01.h"
#include "Stage_M_2F_02.h"
#include "Stage_M_1F_pic.h"

#include "Stage_B_00.h"
#include "Stage_B_01.h"
#include "Stage_B_02.h"
#include "Stage_B_03.h"
#include "Stage_B_04.h"

#include "Stage_G_01.h"
#include "Stage_G_02.h"
#include "Stage_G_03.h"

#include "CItemMenu.h"
#include "CPlayer.h"
#include "CStage.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CStageMgr::CStageMgr()
	: m_arrStage{}
	, m_pCurStage(nullptr)
	, m_pCurStageType(ESTAGE_TYPE::EXIT)
	, m_pPrevStageType(ESTAGE_TYPE::EXIT)
	, m_pPrevDoorNUM(0)
	, m_vTablePos(Vec2 (0,0))
	, m_bRose(false)
	, m_bMStageSubCharOff(false)
	, m_bHaveBlueKey(false)
	, m_bHaveGreenKey(false)
	, m_bMStageVeilOn(false)
	, m_iRoseCount(5)
	, m_bPlayerHit(false)
	, m_bMuseumEventOn(false)
	, m_bEventAnimationOn(false)
	, m_bMonsterBroken(false)
	, m_bHandPopUp(false)
	, m_bAntPic(false)
	, m_bAntPicPutTile(false)
	, m_iAntPicCount(2)
	, m_bRedBall(false)
	, m_bWindow1(false)
	, m_bWindow2(false)
	, pNewSound(nullptr)
	, m_fSoundAddTime(0.f)
	, m_fSoundMaxTime(0.f)
	, m_bBlueDoorOpen(false)
	, m_bGreenDoorOpen(false)
	, m_bMonsterBrokenSound(false)
	, m_kPlayerKeyState(KEY::RIGHT)
{

}

CStageMgr::~CStageMgr()
{
	Safe_Del_Arr(m_arrStage);
}


void CStageMgr::init()
{
	// 모든 스테이지 생성
	m_arrStage[(UINT)ESTAGE_TYPE::TITLE] = new CTitle;
	m_arrStage[(UINT)ESTAGE_TYPE::STARTANIMATION] = new CStartAnimation;
	m_arrStage[(UINT)ESTAGE_TYPE::STARTSCRIPT] = new CStartScript;
	m_arrStage[(UINT)ESTAGE_TYPE::ENDSTAGE] = new EndStage;
	m_arrStage[(UINT)ESTAGE_TYPE::GAMEOVER] = new GameOver;

	m_arrStage[(UINT)ESTAGE_TYPE::TOOL] = new CStage_Tool;
	m_arrStage[(UINT)ESTAGE_TYPE::START] = new CStage_Start;
	m_arrStage[(UINT)ESTAGE_TYPE::PLAY_01] = new CStage_Play01;
	m_arrStage[(UINT)ESTAGE_TYPE::M_1F_00] = new Stage_M_1F_00;
	m_arrStage[(UINT)ESTAGE_TYPE::M_1F_01] = new Stage_M_1F_01;
	m_arrStage[(UINT)ESTAGE_TYPE::M_1F_01_02] = new Stage_M_1F_01_02;
	m_arrStage[(UINT)ESTAGE_TYPE::M_1F_02] = new Stage_M_1F_02;
	m_arrStage[(UINT)ESTAGE_TYPE::M_1F_03] = new Stage_M_1F_03;
	m_arrStage[(UINT)ESTAGE_TYPE::M_1F_pic] = new Stage_M_1F_pic;
	m_arrStage[(UINT)ESTAGE_TYPE::M_2F_01] = new Stage_M_2F_01;
	m_arrStage[(UINT)ESTAGE_TYPE::M_2F_02] = new Stage_M_2F_02;

	m_arrStage[(UINT)ESTAGE_TYPE::B_00] = new Stage_B_00;
	m_arrStage[(UINT)ESTAGE_TYPE::B_01] = new Stage_B_01;
	m_arrStage[(UINT)ESTAGE_TYPE::B_02] = new Stage_B_02;
	m_arrStage[(UINT)ESTAGE_TYPE::B_03] = new Stage_B_03;
	m_arrStage[(UINT)ESTAGE_TYPE::B_04] = new Stage_B_04;

	m_arrStage[(UINT)ESTAGE_TYPE::G_01] = new Stage_G_01;
	m_arrStage[(UINT)ESTAGE_TYPE::G_02] = new Stage_G_02;
	m_arrStage[(UINT)ESTAGE_TYPE::G_03] = new Stage_G_03;

	m_arrStage[(UINT)ESTAGE_TYPE::MENU] = new CItemMenu;



	//m_arrStage[(UINT)ESTAGE_TYPE::PLAY_02] = new CStage_Play02;
	//m_arrStage[(UINT)ESTAGE_TYPE::EXIT] = new CStage_Exit;

	// 현재 스테이지 지정
	ChangeStage(ESTAGE_TYPE::TITLE);
}

void CStageMgr::update()
{
	m_pCurStage->update();
	m_pCurStage->finalupdate();

	if (0.f < m_fSoundMaxTime)
	{
		m_fSoundAddTime += DS;
		pNewSound->SetVolume((1-(m_fSoundAddTime /m_fSoundMaxTime)) * 100);
		if (m_fSoundMaxTime <= m_fSoundAddTime)
		{
			m_fSoundMaxTime = 0.f;
			pNewSound->Stop();
		}
	}
}

void CStageMgr::render(HDC _dc)
{
	m_pCurStage->render(_dc);
}

void CStageMgr::Setbgm(wstring _str)
{
	pNewSound = CResMgr::GetInst()->FindSound(_str);
	pNewSound->PlayToBGM(true);
}


void CStageMgr::ChangeStage(ESTAGE_TYPE _eNextStage)
{
	assert(m_pCurStage != m_arrStage[(UINT)_eNextStage]);

	if(nullptr != m_pCurStage)
		m_pCurStage->Exit();
	
	m_pPrevStageType = m_pCurStageType;
	m_pCurStageType = _eNextStage;
	m_pCurStage = m_arrStage[(UINT)_eNextStage];

	m_pCurStage->Enter();
}

CObj* CStageMgr::GetPlayer()
{
	const vector<CObj*>& vecPlayer = m_pCurStage->GetObjects(EOBJ_TYPE::PLAYER);

	if (vecPlayer.empty())
		return nullptr;

	return vecPlayer[0];
}