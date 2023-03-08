#include "pch.h"
#include "EndStage.h"

#include"CResMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CCamera.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"


EndStage::EndStage()
	: m_pEndTiltleImg(nullptr)
	, m_pImgIB(nullptr)
	, m_fAddTime(0.f)
	, m_bChangeScene(false)
{
	m_pEndTiltleImg = CResMgr::GetInst()->LoadTexture(L"end_tit", L"texture\\ib\\end_tit.bmp");
	m_pImgIB = CResMgr::GetInst()->LoadTexture(L"end_ib", L"texture\\ib\\end_ib.bmp");
}

EndStage::~EndStage()
{
}
void EndStage::init()
{
}

void EndStage::update()
{
	CStage::update();

	if (KTAP(KEY::SPACE)) 
	{
		CCamera::GetInst()->FadeIn(5.f);
		m_bChangeScene = true;
	}
	

	m_fAddTime += DS;
}

void EndStage::render(HDC _dc)
{
	CStage::render(_dc);

	if (!m_bChangeScene)
	{
		BitBlt(_dc
			, 0, 0
			, m_pEndTiltleImg->Width()
			, m_pEndTiltleImg->Height()
			, m_pEndTiltleImg->GetDC()
			, 0, 0
			, SRCCOPY);
	}
	else
	{
		BitBlt(_dc
			, 0, 0
			, m_pImgIB->Width()
			, m_pImgIB->Height()
			, m_pImgIB->GetDC()
			, 0, 0
			, SRCCOPY);
	}
}

void EndStage::Enter()
{
	CCamera::GetInst()->FadeIn(2.f);

	CSound* title = CResMgr::GetInst()->FindSound(L"title");
	title->PlayToBGM(true);
	init();
}

void EndStage::Exit()
{
}

