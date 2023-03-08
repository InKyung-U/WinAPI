#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CCamera.h"

#include "CAnimator.h"
#include "CObj.h"
#include "CTexture.h"

#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCore.h"



CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pAtlas(nullptr)
	, m_iCurIdx(0)
	, m_fAddTime(0.f)
	, m_bFinish(false)
{	 

}

CAnimation::~CAnimation()
{

}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAddTime += DS;

	if (m_fAddTime > m_vecFrm[m_iCurIdx].fDuration)
	{
		m_fAddTime = m_fAddTime - m_vecFrm[m_iCurIdx].fDuration;
		++m_iCurIdx;

		if (m_iCurIdx >= m_vecFrm.size())
		{
			m_iCurIdx -= 1;
			m_bFinish = true;
		}
	}
}

void CAnimation::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetOwner()->GetPos());

	TransparentBlt(_dc
		, int(vRenderPos.x - m_vecFrm[m_iCurIdx].vSize.x / 2.f + m_vecFrm[m_iCurIdx].vOffset.x)
		, int(vRenderPos.y - m_vecFrm[m_iCurIdx].vSize.y / 2.f + m_vecFrm[m_iCurIdx].vOffset.y)
		, int(m_vecFrm[m_iCurIdx].vSize.x)
		, int(m_vecFrm[m_iCurIdx].vSize.y)
		, m_pAtlas->GetDC()
		, int(m_vecFrm[m_iCurIdx].vLeftTop.x)
		, int(m_vecFrm[m_iCurIdx].vLeftTop.y)
		, int(m_vecFrm[m_iCurIdx].vSize.x)
		, int(m_vecFrm[m_iCurIdx].vSize.y)
		, RGB(255, 0, 255));
}

void CAnimation::Create(const wstring& _strName, CTexture* _pAtlasTex
	, Vec2 _vLeftTop, Vec2 _vSize, float _fXDistance, float _fDuration, UINT _iFrmCount)
{
	m_strName = _strName;

	m_pAtlas = _pAtlasTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrmCount; ++i)
	{
		frm.vLeftTop = Vec2(_vLeftTop.x + (float)i * _fXDistance, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.fDuration = _fDuration;
		frm.vOffset = Vec2(0.f, 0.f);
		m_vecFrm.push_back(frm);
	}
}

CObj* CAnimation::GetOwner()
{
	return m_pAnimator->GetOwner();
}

void CAnimation::Save(const wstring& _strRelativeFolderPath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFolderPath;
	strFilePath += m_strName;
	strFilePath += L".anim";


	FILE* pFile = nullptr;
		
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
		
	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드 : %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHwnd(), szErr , L"애니메이션 저장 오류", MB_OK);
	}
	
		
	// 애니메이션 데이터를 저장
	// Animation 이름 정보	
	fwprintf_s(pFile, L"[Animation_Name]\n");
	fwprintf_s(pFile, m_strName.c_str());	
	fwprintf_s(pFile, L"\n\n");

	// 참조하는 Atlas Texture 정보
	fwprintf_s(pFile, L"[Atlas_Texture_Name]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[Atlas_Texture_Path]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");
	
	// 각 프레임 정보
	fwprintf_s(pFile, L"[Frame_Info]\n");
	fwprintf_s(pFile, L"[Frame_Count]\n");
	fwprintf_s(pFile, L"%d\n", (int)m_vecFrm.size());
	fwprintf_s(pFile, L"\n");

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[Frame_Idx]\n");
		fwprintf_s(pFile, L"%d\n", (int)i);

		fwprintf_s(pFile, L"[Left_Top]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		fwprintf_s(pFile, L"[Size]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vSize.x, m_vecFrm[i].vSize.y);

		fwprintf_s(pFile, L"[Offset]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		fwprintf_s(pFile, L"[Duration]\n");
		fwprintf_s(pFile, L"%f\n\n", m_vecFrm[i].fDuration);		
	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;	

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드 : %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHwnd(), szErr, L"애니메이션 로딩 오류", MB_OK);
	}
	wchar_t szBuff[256] = L"";

	// Animation 이름 불러오기
 	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);

	m_strName = szBuff;

	// 참조하는 Atlas Texture 정보
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);	
	
	wstring strKey = szBuff;	

	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	
	wstring strPath = szBuff;

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strPath);


	// 각 프레임 정보
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);

	int iFrameCount = 0;
	fwscanf_s(pFile, L"%d", &iFrameCount);
	

	for (int i = 0; i < iFrameCount; ++i)
	{
		tAnimFrm frm = {};
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%s", szBuff, 256);
				
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);

		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);

		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);

		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f", &frm.fDuration);

		m_vecFrm.push_back(frm);
	}

	fclose(pFile);
}