#include "pch.h"
#include "CStage_Start.h"

#include "CStageMgr.h"
#include "CKeyMgr.h"

#include "CTexture.h"


CStage_Start::CStage_Start()
{
}

CStage_Start::~CStage_Start()
{
}

void CStage_Start::init()
{

}

void CStage_Start::update()
{
	CStage::update();

	if (KTAP(KEY::ENTER))
	{
		ChangeStage(ESTAGE_TYPE::PLAY_01);
	}
}

void CStage_Start::render(HDC _dc)
{
	CStage::render(_dc);

	TextOut(_dc, 10, 10, L"Here is Start Stage", (int)wcslen(L"Here is Start Stage"));
}

void CStage_Start::Enter()
{
	init();
}

void CStage_Start::Exit()
{

}