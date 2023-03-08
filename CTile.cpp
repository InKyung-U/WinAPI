#include "pch.h"
#include "CTile.h"

#include "CCamera.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"
#include "CStageMgr.h"



CTile::CTile()
	: m_iImgIdx(-1)
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\tile\\TILE.bmp");
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (-1 == m_iImgIdx || nullptr == m_pAtlas)
		return;

	UINT iWidth = m_pAtlas->Width();
	UINT iHeight = m_pAtlas->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iMaxCount = iMaxCol * iMaxRow;

	// 최대 인덱스를 넘어 선 경우
	if (m_iImgIdx >= iMaxCount)
		return;


	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	UINT iRow = m_iImgIdx / iMaxCol;
	UINT iCol = m_iImgIdx % iMaxCol;
		
	
	/*BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = 0;

	AlphaBlend(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)vSize.x
		, (int)vSize.y
		, m_pAtlas->GetDC()
		, iCol * TILE_SIZE
		, iRow * TILE_SIZE
		, TILE_SIZE, TILE_SIZE
		, bf);*/


	BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)vSize.x
		, (int)vSize.y
		, m_pAtlas->GetDC()
		, iCol * TILE_SIZE
		, iRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::AddImgIdx()
{
	if (nullptr == m_pAtlas)
	{
		m_iImgIdx = -1;
	}

	if (++m_iImgIdx >= m_pAtlas->Width() / TILE_SIZE * m_pAtlas->Height() / TILE_SIZE)
	{
		m_iImgIdx = 0;
	}
}

bool CTile::CheckImgIdxToMove()
{
	// 움직일 수 있는걸 조건으로 주자
	if (m_iImgIdx == 1 || m_iImgIdx == 2 || m_iImgIdx == 12 || m_iImgIdx == 13 || m_iImgIdx == 14
		|| m_iImgIdx == 16 || m_iImgIdx == 19 || m_iImgIdx == 20 || m_iImgIdx == 24 || m_iImgIdx == 25 || m_iImgIdx == 27
		|| m_iImgIdx == 28 || m_iImgIdx == 31 || m_iImgIdx == 37 || m_iImgIdx == 45 || m_iImgIdx == 46 || m_iImgIdx == 50
		|| m_iImgIdx == 53 || m_iImgIdx == 18 || m_iImgIdx == 21)
	{
		if (m_iImgIdx == 18 || m_iImgIdx == 21)
		{
			if (CStageMgr::GetInst()->IsAntPicPutTile())
			{
				if (0 < CStageMgr::GetInst()->returnAntPicCount())
					return true;
				else
					return false;
			}
			else false;
		}
		else
			return true;
	}
	else
		return false;
}

bool CTile::IsMouseOn(Vec2 _vMouseRealPos)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (vPos.x <= _vMouseRealPos.x && _vMouseRealPos.x <= (vPos.x + vScale.x)
		&& vPos.y <= _vMouseRealPos.y && _vMouseRealPos.y <= (vPos.y + vScale.y))
	{
		return true;
	}

	return false;
}



void CTile::SaveToFile(FILE* _pFile)
{
	// 타일의 위치
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	fwrite(&vPos, sizeof(Vec2), 1, _pFile);
	fwrite(&vScale, sizeof(Vec2), 1, _pFile);

	// 아틀라스 텍스쳐
	UINT HasAltasTex = !!m_pAtlas;	
	fwrite(&HasAltasTex, sizeof(UINT), 1, _pFile);

	// 참조하고 있는 아틀라스 텍스쳐가 있다면
	if (HasAltasTex)
	{
		SaveWString(m_pAtlas->GetKey(), _pFile);
		SaveWString(m_pAtlas->GetRelativePath(), _pFile);
	}

	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::LoadFromFile(FILE* _pFile)
{
	Vec2 vPos;
	Vec2 vScale;

	fread(&vPos, sizeof(Vec2), 1, _pFile);
	fread(&vScale, sizeof(Vec2), 1, _pFile);

	UINT HasAltasTex = !!m_pAtlas;
	fread(&HasAltasTex, sizeof(UINT), 1, _pFile);

	// 참조하고 있는 아틀라스 텍스쳐가 있다면
	if (HasAltasTex)
	{
		wstring strKey, strPath;
		LoadWString(strKey, _pFile);
		LoadWString(strPath, _pFile);

		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strPath);
	}

	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
