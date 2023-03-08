#include "pch.h"
#include "CStage.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CObj.h"
#include "CTile.h"
#include "CTable.h"
#include "CTexture.h"
#include "CUI.h"
#include "CPanel.h"

#include "CCamera.h"



CStage::CStage()
	: m_iTileXCount(0)
	, m_iTileYCount(0)
	, m_pVeilTex(nullptr)
	, pParentUI(nullptr)
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"Veil", (UINT)vResolution.x, (UINT)vResolution.y);
}

CStage::~CStage()
{
	Clear();
}

void CStage::update()
{
	for (UINT i = 0; i < (UINT)EOBJ_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j]->IsDead())
				continue;
			
			m_arrObj[i][j]->update();
		}
	}	

	if (KTAP(KEY::I))
	{
		if (CStageMgr::GetInst()->GetCurStageType() != ESTAGE_TYPE::MENU)
		{
			Vec2 playerPos = CStageMgr::GetInst()->GetCurStage()->GetPlayer()->GetPos();
			CStageMgr::GetInst()->SetPlayerPos(playerPos);
			ChangeStage(ESTAGE_TYPE::MENU);
		}
	}


	if (CStageMgr::GetInst()->IsPlayerHaveRose())
	{
		if (pParentUI == nullptr)
		{
			CStageMgr::GetInst()->SetRoseCount(CStageMgr::GetInst()->GetRoseCount());

			// UI �����
			Vec2 vScale = Vec2(120, 160);
			Vec2 vPos = Vec2(0.f, 0.f);
			// UI 1
			pParentUI = new CPanel;
			pParentUI->SetPos(vPos);
			pParentUI->SetScale(vScale);

			AddObject(pParentUI, EOBJ_TYPE::UI);
		}
	}

}

void CStage::finalupdate()
{
	for (UINT i = 0; i < (UINT)EOBJ_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j]->IsDead())
				continue;

			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CStage::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)EOBJ_TYPE::END; ++i)
	{
		if (i == (UINT)EOBJ_TYPE::TILE)
		{
			render_tile(_dc);
		}
		if (i == (UINT)EOBJ_TYPE::VEIL)
		{
			if(CStageMgr::GetInst()->IsMStageVeilOn())
				render_veil(_dc);
		}
		else
		{
			vector<CObj*>::iterator iter = m_arrObj[i].begin();

			for (; iter != m_arrObj[i].end(); )
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrObj[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}

}


void CStage::render_tile(HDC _dc)
{
	// ī�޶� �����ִ� �߽� ��ǥ
	Vec2 vLookAt = CCamera::GetInst()->GetLookAtPos();

	Vec2 vLT = vLookAt - Vec2(CCore::GetInst()->GetResolution()) / 2.f;

	// ī�޶� �����ִ� ������ ��, �� ����
	int iLTCol = (int)vLT.x / TILE_SIZE;
	int iLTRow = (int)vLT.y / TILE_SIZE;
	
	// ȭ���� Ÿ�Ϸ� ���� ä���� �� �ִ� ��, �� ����
	int iMaxCol = CCore::GetInst()->GetResolution().x / TILE_SIZE + 2;
	int iMaxRow = CCore::GetInst()->GetResolution().y / TILE_SIZE + 2;

	// ȭ�� ���� �ʰ����� ���ϰ� ���� ����
	if (iLTCol + iMaxCol > GetTileXCount())
	{
		iMaxCol -= iLTCol + iMaxCol - GetTileXCount();
	}
	// ȭ�� ���� �ʰ����� ���ϰ� ���� ����
	if (vLT.x < 0.f)
	{
		iMaxCol += (int)vLT.x / TILE_SIZE;
		iLTCol = 0;
	}

	// ȭ�� �Ʒ��� �ʰ����� ���ϰ� ���� ����
	if (iLTRow + iMaxRow > GetTileYCount())
	{
		iMaxRow -= iLTRow + iMaxRow - GetTileYCount();		
	}

	// ȭ�� ���� �ʰ����� ���ϰ� ����
	if (vLT.y < 0.f)
	{
		iMaxRow += (int)vLT.y / TILE_SIZE;		
		iLTRow = 0;
	}

	// �ش� ��, �࿡ �ش��ϴ� Ÿ���� 1���� �ε��� ����
	int iLTIdx = GetTileXCount() * iLTRow + iLTCol;

	// Ÿ�Ͽ�����Ʈ ����
	vector<CObj*>& vecTile = m_arrObj[(UINT)EOBJ_TYPE::TILE];

	for (int j = 0; j < iMaxRow; ++j)
	{
		int iStartIdx = iLTIdx + (GetTileXCount() * j);

		for (int i = iStartIdx; i < iStartIdx + iMaxCol; ++i)
		{
			vecTile[i]->render(_dc);
		}
	}	
}

void CStage::render_veil(HDC _dc)
{
	UINT iWidth = m_pVeilTex->Width();
	UINT iHeight = m_pVeilTex->Height();
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = BYTE(255.f * 0.5f);
	bf.AlphaFormat = 0;

	if (CStageMgr::GetInst()->IsSubCharOff())
	{
		AlphaBlend(_dc
			, 0, 0
			, iWidth, iHeight
			, m_pVeilTex->GetDC()
			, 0, 0
			, iWidth, iHeight
			, bf);
	}
}



void CStage::CreateTile(UINT _iCol, UINT _iRow)
{	
	Clear(EOBJ_TYPE::TILE);

	// Ÿ�� ����, ���� ���� ����
	m_iTileXCount = _iCol;
	m_iTileYCount = _iRow;


	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
			pTile->SetPos(Vec2(0.f + 64.f * (float)iCol, 0.f + 64.f * (float)iRow));
			pTile->SetImgIdx(0);

			AddObject(pTile, EOBJ_TYPE::TILE);
		}
	}
}

void CStage::LoadTileFromFile(const wstring& _strRelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"rb");

	assert(pFile);

	// Tile ���� ���� ����
	UINT iTileX = 0, iTileY = 0;

	if (pFile != nullptr)
	{
		fread(&iTileX, sizeof(UINT), 1, pFile);
		fread(&iTileY, sizeof(UINT), 1, pFile);
	}
	CreateTile(iTileX, iTileY);

	const vector<CObj*>& vecTile = GetObjects(EOBJ_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		CTile* pTile = (CTile*)vecTile[i];

		pTile->LoadFromFile(pFile);
	}

	if (pFile != nullptr)
		fclose(pFile);
}

CObj* CStage::GetPlayer()
{
	vector<CObj*>& vecPlayer = m_arrObj[(UINT)EOBJ_TYPE::PLAYER];
	return vecPlayer[0];
}

CTile* CStage::GetPosTile(UINT _row, UINT _col)
{
	vector<CObj*>& vecTile = m_arrObj[(UINT)EOBJ_TYPE::TILE];	

	if ((CTile*)vecTile[_row * m_iTileXCount + _col] == nullptr)
		return nullptr;
	else
		return (CTile*)vecTile[_row * m_iTileXCount + _col];
}

void CStage::StageAdjustment()
{
	UINT XTileCount = CStageMgr::GetInst()->GetCurStage()->GetTileXCount();
	UINT YTileCount = CStageMgr::GetInst()->GetCurStage()->GetTileYCount();

	UINT Width = XTileCount * TILE_SIZE;
	UINT Height = YTileCount * TILE_SIZE;

	CCamera::GetInst()->CameraAdjustment(Width, Height);

}

CTable* CStage::GetStageTable()
{
	vector<CObj*>& vecTable = m_arrObj[(UINT)EOBJ_TYPE::TABLE];
	
	if ((CTable*)vecTable[0] != nullptr)
		return (CTable*)vecTable[0];
	else
		return nullptr;
}

bool CStage::IsTableExist()
{
	vector<CObj*>& vecTable = m_arrObj[(UINT)EOBJ_TYPE::TABLE];

	if (vecTable.size() == 0)
		return false;
	else
		return true;
}

void CStage::DeleteScript()
{
	vector<CObj*>& vecObj = m_arrObj[(UINT)EOBJ_TYPE::SCRIPTUI];
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		delete vecObj[i];
	}
	vecObj.clear();
}

void CStage::Clear(EOBJ_TYPE _type)
{
	vector<CObj*>& vecObj = m_arrObj[(UINT)_type];
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		delete vecObj[i];
	}
	vecObj.clear();
}

void CStage::Clear()
{
	for (UINT i = 0; i < (UINT)EOBJ_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			assert(m_arrObj[i][j]);
			delete m_arrObj[i][j];
		}
		m_arrObj[i].clear();
	}		
}