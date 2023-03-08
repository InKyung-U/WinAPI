#include "pch.h"
#include "CBtnUI.h"

#include "CStageMgr.h"
#include "CStage_Tool.h"

#include "resource.h"
#include "CKeyMgr.h"

CBtnUI::CBtnUI()
{
}

CBtnUI::~CBtnUI()
{
}


void CBtnUI::update()
{
	// UI Drag Drop
	//DragDrop_update();
	

	// 부모 업데이트(위치 업데이트, 자식 UI 업데이트)
	CUI::update();
}

void CBtnUI::MouseLbtnClicked(Vec2 _vMousePos)
{
	CUI::MouseLbtnClicked(_vMousePos);

	/*CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();

	CStage_Tool* pToolStage = dynamic_cast<CStage_Tool*>(pCurStage);

	if (!!pToolStage)
	{
		pToolStage->Proc(ID_TILECOUNT);
	}	*/
}


