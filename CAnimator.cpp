#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"


CAnimator::CAnimator()
	: CComponent(ECOM_TYPE::ANIMATOR)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _origin)
	: CComponent(_origin)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
	map<wstring, CAnimation*>::const_iterator iter = _origin.m_mapAnim.begin();
	for (; iter != _origin.m_mapAnim.end(); ++iter)
	{
		CAnimation* pCloneAnim = iter->second->Clone();

		pCloneAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pCloneAnim));
	}
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		delete iter->second;
	}
	m_mapAnim.clear();
}

void CAnimator::update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->Reset();
		}
	}		
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->render(_dc);
	}
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	assert(m_pCurAnim);

	m_bRepeat = _bRepeat;
}


CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if(iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
	CAnimation* pAnim = new CAnimation;

	pAnim->Load(_strRelativeFilePath);
	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}


void CAnimator::CreateAnimation(const wstring& _strAnimName, CTexture* _pAtlasTex
	, Vec2 _vLeftTop, Vec2 _vSize, float _fXDistance, float _fDuration, UINT _iFrmCount)
{
	CAnimation* pAnim = FindAnimation(_strAnimName);
	assert(!pAnim);

	pAnim = new CAnimation;
	pAnim->Create(_strAnimName, _pAtlasTex, _vLeftTop, _vSize, _fXDistance, _fDuration, _iFrmCount);
	pAnim->m_pAnimator = this;

	m_mapAnim.insert(make_pair(_strAnimName, pAnim));
}