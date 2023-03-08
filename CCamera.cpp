#include "pch.h"
#include "CCamera.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CStageMgr.h"
#include "CStage.h"
#include "CPlayer.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pVeilTex(nullptr)	
	, m_second(0)
{
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_vLookAt = vResolution / 2.f;


	if (nullptr == m_pVeilTex)
	{
		m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"Veil", (UINT)vResolution.x, (UINT)vResolution.y);		
	}

}

void CCamera::update()
{
	if (CStageMgr::GetInst()->GetPlayer() != nullptr)
	{
		Vec2 playerPos = CStageMgr::GetInst()->GetPlayer()->GetPos();
		m_vLookAt = playerPos;
	}
	UINT XTile = CStageMgr::GetInst()->GetCurStage()->GetTileXCount();
	UINT YTile = CStageMgr::GetInst()->GetCurStage()->GetTileYCount();

	CameraAdjustment(XTile * TILE_SIZE, YTile * TILE_SIZE);


	if (KPRESSED(KEY::NUM6))
	{
		m_vLookAt.x += DS * 1000.f;
	}

	if (KPRESSED(KEY::NUM4))
	{
		m_vLookAt.x -= DS * 1000.f;
	}

	if (KPRESSED(KEY::NUM8))
	{
		m_vLookAt.y -= DS * 1000.f;
	}

	if (KPRESSED(KEY::NUM5))
	{
		m_vLookAt.y += DS * 1000.f;
	}	

	Vec2 vCenter = CCore::GetInst()->GetResolution();
	vCenter /= 2.f;
	m_vDiff = m_vLookAt - vCenter;
}

void CCamera::render(HDC _dc)
{
	while (true)
	{
		if (m_EffectQueue.empty())
			return;

		tCamEffect& effect = m_EffectQueue.front();
		effect.fAddTime += DS;

		if (effect.fAddTime > effect.fEffectMaxTime)
		{
			m_EffectQueue.pop_front();			
		}
		else
		{
			break;
		}
	}
	
	tCamEffect& effect = m_EffectQueue.front();	

	float fAlpha = 0.f;
	if (ECAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		fAlpha = effect.fAddTime / effect.fEffectMaxTime;
	}
	else if (ECAM_EFFECT::FADE_IN == effect.eEffect)
	{
		fAlpha = (1.f - (effect.fAddTime / effect.fEffectMaxTime));
	}
	else if (ECAM_EFFECT::TURNOFF_HALF == effect.eEffect)
	{
		fAlpha = 0.5f;
	}
	else if (ECAM_EFFECT::TURNON == effect.eEffect)
	{
		fAlpha = 0.1f;
	}


	UINT iWidth = m_pVeilTex->Width();
	UINT iHeight = m_pVeilTex->Height();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = BYTE(fAlpha * 255.f);
	bf.AlphaFormat = 0;

	if (fAlpha <= 0.f)
	{
		return;
	}



	AlphaBlend(_dc
		, 0, 0
		, iWidth, iHeight
		, m_pVeilTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, bf);

}

void CCamera::CameraAdjustment(UINT _tileWidth, UINT _tileHeight)
{
	// 해상도
	Vec2 vWindowSize = CCore::GetInst()->GetResolution();

	// x 값 확인.
	// 1. 음수일때
	// 2. m_vLookAt + 해상도 가 타일의 크기를 넘었을 때

	if (m_vLookAt.x - (vWindowSize.x / 2) <= 0)
	{
		m_vLookAt.x = vWindowSize.x / 2;
	}
	if (_tileWidth < m_vLookAt.x + (vWindowSize.x / 2))
	{
		m_vLookAt.x = _tileWidth - vWindowSize.x / 2;
	}
	if (m_vLookAt.y - (vWindowSize.y / 2) <= 0)
	{
		m_vLookAt.y = vWindowSize.y / 2;
	}
	if (_tileHeight < m_vLookAt.y + (vWindowSize.y / 2))
	{
		m_vLookAt.y = _tileHeight - vWindowSize.y / 2;
	}

}

bool CCamera::IsCameraMove(UINT _stageWidth, UINT _stageHeight, KEY _pressedKey, Vec2 _playerPos)
{
	Vec2 vWndSize = CCore::GetInst()->GetResolution();
	switch (_pressedKey)
	{	
	case KEY::LEFT:
		if (m_vLookAt.x <= _playerPos.x)
			return false;
		else
		{
			if (m_vLookAt.x - vWndSize.x/2 <= 0)
				return false;
			return true;
		}
		break;
	case KEY::RIGHT:
		if (m_vLookAt.x >= _playerPos.x)
			return false;
		else
		{
			if (_stageWidth <= m_vLookAt.x + vWndSize.x / 2)
				return false;
			return true;
		}
		break;
	case KEY::UP:
		if (m_vLookAt.y <= _playerPos.y)
			return false;
		else
		{
			if (m_vLookAt.y - vWndSize.y / 2 <= 0)
				return false;
			return true;
		}
		break;
	case KEY::DOWN:
		if (m_vLookAt.y >= _playerPos.y)
			return false;
		else
		{
			if (_stageHeight <= m_vLookAt.y + vWndSize.y / 2)
				return false;
			return true;
		}
		break;
	}
	return false;

}
