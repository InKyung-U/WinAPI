#include "pch.h"
#include "GameOver.h"
#include"CResMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CStageMgr.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

GameOver::GameOver()
	: m_pGameOverImg(nullptr)
{
	m_pGameOverImg = CResMgr::GetInst()->LoadTexture(L"gameover", L"texture\\ib\\gameover.bmp");
}

GameOver::~GameOver()
{
}

void GameOver::init()
{
}

void GameOver::update()
{
	CStage::update();

	if (KTAP(KEY::ENTER))
	{
		ChangeStage(ESTAGE_TYPE::G_01);
	}
}

void GameOver::render(HDC _dc)
{
	CStage::render(_dc);

	BitBlt(_dc
		, 0, 0
		, m_pGameOverImg->Width()
		, m_pGameOverImg->Height()
		, m_pGameOverImg->GetDC()
		, 0, 0
		, SRCCOPY);
}

void GameOver::Enter()
{
	CCamera::GetInst()->FadeIn(2.f);

	CSound* gameover = CResMgr::GetInst()->FindSound(L"gameover");
	gameover->PlayToBGM(true);
	init();
}

void GameOver::Exit()
{
}
