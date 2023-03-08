#include "pch.h"
#include "CTitle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CTitle::CTitle()
	: m_pTiltleImg(nullptr)
	, m_pScript1{}
	, m_pScript2{}
	, m_pScriptBox(nullptr)
	, m_iScriptNum(1)
	, m_pSelectBox(nullptr)
	, m_fAddTime(0.f)
	, m_vSelectBoxPos{}
	, m_fAlpha(0.2f)
{
	m_pTiltleImg = CResMgr::GetInst()->LoadTexture(L"TitleImage", L"texture\\ib\\title.bmp");
	m_pScriptBox = CResMgr::GetInst()->LoadTexture(L"TitleBox", L"texture\\ib\\mainBox.bmp");
	m_pSelectBox = CResMgr::GetInst()->LoadTexture(L"SelectBox", L"texture\\whiteBox.bmp");
	m_pScript1 = L"시작하기";
	m_pScript2 = L"나가기";

	m_vSelectBoxPos = Vec2(312 + 30, 500 + 30);

	// Sound 로드 테스트
	//CResMgr::GetInst()->LoadSound(L"title", L"sound\\title.wav");
	//CSound* pNewSound = CResMgr::GetInst()->FindSound(L"title");
	//
	//pNewSound->PlayToBGM(true);
	//pNewSound->Play();
}

CTitle::~CTitle()
{
}


void CTitle::init()
{
}

void CTitle::update()
{
	CStage::update();
	m_fAddTime += DS;

	if (0.6f <= m_fAddTime)
	{
		if (m_fAlpha == 0.f)
			m_fAlpha = 0.2f;
		else
			m_fAlpha = 0.f;

		m_fAddTime = 0;
	}

	CSound* select = CResMgr::GetInst()->FindSound(L"select");

	if (KTAP(KEY::SPACE))
	{
		if (m_iScriptNum == 1)
		{
			ChangeStage(ESTAGE_TYPE::STARTSCRIPT);
			select->Play();
			//ChangeStage(ESTAGE_TYPE::G_01);
		}
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

	if(m_iScriptNum == 1)
		m_vSelectBoxPos = Vec2(312 + 30, 500 + 30);
	if (m_iScriptNum == 2)
		m_vSelectBoxPos = Vec2(312 + 30, 500 + 30 + 75);
}

void CTitle::render(HDC _dc)
{
	BitBlt(_dc
	, 0,0
	, m_pTiltleImg->Width()
	, m_pTiltleImg->Height()
	, m_pTiltleImg->GetDC()
	, 0, 0
	, SRCCOPY);

	BitBlt(_dc
		, 312, 500
		, m_pScriptBox->Width()
		, m_pScriptBox->Height()
		, m_pScriptBox->GetDC()
		, 0, 0
		, SRCCOPY);

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
	SetRect(&rectangle1, 350, 545, 350 + 314, 545 + 63);
	DrawText(_dc, m_pScript1.c_str(), -1, &rectangle1, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL);

	RECT rectangle2;
	SetRect(&rectangle2, 350, 545 + 73, 350 + 314, 545 + 103 + 33);
	DrawText(_dc, m_pScript2.c_str(), -1, &rectangle2, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL);
}

void CTitle::Enter()
{
	init();
}

void CTitle::Exit()
{
}
