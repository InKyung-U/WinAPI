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

	// ���콺 Ŭ�� �߻� -> �ش� Ÿ�� ���� -> Ÿ�� �ε��� ����
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

	// Ÿ�� ������ ��� ��ġ�� Ŭ���� ���
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
	// �޴� �߰�
	SetMenu(CCore::GetInst()->GetMainWndHwnd(), m_hMenu);	
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), true);

	// Ÿ�� �ӽ� ����
	CreateTile(10, 10);

	// UI �����
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
	// �޴� ����
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

		// Tile ���� ���� ����
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
		// ���� Ÿ�ϵ����� ���� ���
		wstring strFullPath = szName;

		// LoadTileFromFile �Լ��� ����θ� �䱸�ϱ� ������,
		// Content ���� ������ ��κκ��� �����ؼ� �޺κ��� �����Ѵ�.
		// ���� ��ο��� ��ġ�� Content ���������� ��� ��ġ�� �ڿ��� ã�Ƽ�
		// �ű⼭ ���ڿ� ���κб����� �߶󳽴�.
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
// TileCount ���̾�α��� ���� �޼��� ó���� �Լ�
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
			// EditControl �� �Է��� ���� �����´�.			
			g_iCol = GetDlgItemInt(hDlg, IDC_EDIT1, (BOOL*)false, (BOOL)true);
			g_iRow = GetDlgItemInt(hDlg, IDC_EDIT2, (BOOL*)false, (BOOL)true);

			// EndDialog 2��° ���ڴ� Dialog ����� ��ȯ�Ǵ� ���̴�.
			// � ��ư�� ������ ����� ���� �˸��� ���ؼ� ���� ��ư�� ���̵��� �־� ���´�.
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}		
	}
	return (INT_PTR)FALSE;
}
