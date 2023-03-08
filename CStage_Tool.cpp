#include "pch.h"
#include "CStage_Tool.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "resource.h"

#include "CTile.h"
#include "CUI.h"
#include "CBtnUI.h"
#include "CPanel.h"

UINT g_iCol = 0;
UINT g_iRow = 0;


CStage_Tool::CStage_Tool()
	: m_hMenu(nullptr)
	, m_eMode(TOOL_MODE::TILE)
{
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
}

CStage_Tool::~CStage_Tool()
{
	DestroyMenu(m_hMenu);
}

void CStage_Tool::init()
{

}

void CStage_Tool::update()
{
	CStage::update();

	switch (m_eMode)
	{
	case TOOL_MODE::TILE:
		update_tile();
		break;
	case TOOL_MODE::OBJECT:

		break;
	case TOOL_MODE::ANIMATION:

		break;	
	}

	if (KTAP(KEY::NUM1))
	{
		ChangeStage(ESTAGE_TYPE::PLAY_01);
	}
}


void CStage_Tool::update_tile()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	// 마우스 클릭 발생 -> 해당 타일 접근 -> 타일 인덱스 증가
	if (KTAP(KEY::LBTN))
	{
		CTile* pClickedTile = GetTile(CKeyMgr::GetInst()->GetMousePos());

		if (nullptr != pClickedTile)
		{
			pClickedTile->AddImgIdx();
		}
	}
}

CTile* CStage_Tool::GetTile(Vec2 _vMousePos)
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vMouseRealPos = CCamera::GetInst()->GetRealPos(vMousePos);

	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	UINT iRow = (UINT)vMouseRealPos.y / TILE_SIZE;
	UINT iCol = (UINT)vMouseRealPos.x / TILE_SIZE;

	// 타일 영역을 벗어난 위치를 클릭한 경우
	if (iTileYCount <= iRow || iTileXCount <= iCol || vMouseRealPos.x < 0.f || vMouseRealPos.y < 0.f)
	{
		return nullptr;
	}

	UINT iIdx = iTileXCount * iRow + iCol;
	const vector<CObj*>& vecTile = GetObjects(EOBJ_TYPE::TILE);

	CTile* pTile = dynamic_cast<CTile*>(vecTile[iIdx]);
	assert(pTile);
	return pTile;
}


void CStage_Tool::render(HDC _dc)
{
	CStage::render(_dc);


}

void CStage_Tool::Enter()
{
	// 메뉴 추가
	SetMenu(CCore::GetInst()->GetMainWndHwnd(), m_hMenu);	
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), true);

	// 타일 임시 생성
	CreateTile(10, 10);

	// UI 만들기
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vScale = Vec2(200.f, 300.f);
	Vec2 vPos = Vec2(vResolution.x - vScale.x, 0.f);

	CUI* pParentUI = nullptr;
	CUI* pChildUI = nullptr;

	// UI 1
	pParentUI = new CPanel;
	pParentUI->SetPos(vPos);
	pParentUI->SetScale(vScale);	
	
	pChildUI = new CBtnUI;
	pChildUI->SetPos(Vec2(10.f, 10.f));
	pChildUI->SetScale(Vec2(80.f, 30.f));

	pParentUI->AddChildUI(pChildUI);
	AddObject(pParentUI, EOBJ_TYPE::UI);

	// UI 2
	CUI* pCloneUI = pParentUI->Clone();
	pCloneUI->SetPos(pCloneUI->GetPos() - Vec2(400.f, 0.f));	
	AddObject(pCloneUI, EOBJ_TYPE::UI);
}

void CStage_Tool::Exit()
{
	// 메뉴 제거
	SetMenu(CCore::GetInst()->GetMainWndHwnd(), nullptr);
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), false);
}

void CStage_Tool::Proc(UINT _id)
{
	switch (_id)
	{
	case ID_TILECOUNT:
		PopupCreateTile();
		break;
	case ID_TILE_SAVE:
		SaveTile();
		break;
	case ID_TILE_LOAD:
		LoadTile();
		break;
	}
}

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CStage_Tool::PopupCreateTile()
{
	DWORD dwID = DialogBox(nullptr, MAKEINTRESOURCE(IDD_TILE_COUNT), CCore::GetInst()->GetMainWndHwnd(), TileCountProc);

	if (IDOK == dwID)
	{
		CreateTile(g_iCol, g_iRow);
	}
}

void CStage_Tool::SaveTile()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainWndHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn))
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szName, L"wb");

		assert(pFile);

		// Tile 가로 세로 개수
		UINT iTileX = GetTileXCount();
		UINT iTileY = GetTileYCount();

		fwrite(&iTileX, sizeof(UINT), 1, pFile);
		fwrite(&iTileY, sizeof(UINT), 1, pFile);

		const vector<CObj*>& vecTile = GetObjects(EOBJ_TYPE::TILE);

		for (size_t i = 0; i < vecTile.size(); ++i)
		{
			CTile* pTile = (CTile*)vecTile[i];

			pTile->SaveToFile(pFile);
		}


		fclose(pFile);		
	}
}

void CStage_Tool::LoadTile()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainWndHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		// 최종 타일데이터 파일 경로
		wstring strFullPath = szName;

		// LoadTileFromFile 함수는 상대경로를 요구하기 때문에,
		// Content 폴더 까지의 경로부분을 제거해서 뒷부분을 전달한다.
		// 최종 경로에서 겹치는 Content 폴더까지의 경로 위치를 뒤에서 찾아서
		// 거기서 문자열 끝부분까지를 잘라낸다.
		size_t iFindIdx = strFullPath.rfind(CPathMgr::GetInst()->GetContentPath());

		if (-1 != iFindIdx)
		{
			iFindIdx = iFindIdx + wstring(CPathMgr::GetInst()->GetContentPath()).length();
			wstring strRelativePath = strFullPath.substr(iFindIdx, strFullPath.length());
			LoadTileFromFile(strRelativePath);
		}
	}
}




// ===========================================
// TileCount 다이얼로그의 전용 메세지 처리기 함수
// ===========================================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// EditControl 에 입력한 값을 가져온다.			
			g_iCol = GetDlgItemInt(hDlg, IDC_EDIT1, (BOOL*)false, (BOOL)true);
			g_iRow = GetDlgItemInt(hDlg, IDC_EDIT2, (BOOL*)false, (BOOL)true);

			// EndDialog 2번째 인자는 Dialog 종료시 반환되는 값이다.
			// 어떤 버튼이 눌려서 종료된 건지 알리기 위해서 눌린 버튼의 아이디값을 넣어 놓는다.
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}		
	}
	return (INT_PTR)FALSE;
}
