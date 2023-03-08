#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	Safe_Del_Map(m_mapTex);
	Safe_Del_Map(m_mapSound);
	/*map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
	m_mapTex.clear();*/
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{	
	CRes* pNewTex = FindTexture(_strKey);

	// Ű���� �ش��ϴ� �ؽ��İ� �̹� �ε��� �Ǿ�������...
	if (nullptr != pNewTex)
	{
		// ���� �ε��� �ؽ��ĸ� ��ȯ
		return (CTexture*)pNewTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pNewTex = new CTexture;
	if (FAILED(pNewTex->Load(strFilePath)))
	{
		return nullptr;
	}

	pNewTex->SetKey(_strKey);
	pNewTex->SetRelativePath(_strRelativePath);
	m_mapTex.insert(make_pair(_strKey, (CTexture*)pNewTex));

	return (CTexture*)pNewTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pNewTex = FindTexture(_strKey);

	// Ű���� �ش��ϴ� �ؽ��İ� �̹� �ε��� �Ǿ�������...
	if (nullptr != pNewTex)
	{
		// ���� �ε��� �ؽ��ĸ� ��ȯ
		return (CTexture*)pNewTex;
	}

	pNewTex = new CTexture;
	pNewTex->Create(_iWidth, _iHeight);

	pNewTex->SetKey(_strKey);	
	m_mapTex.insert(make_pair(_strKey, (CTexture*)pNewTex));

	return pNewTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	assert(nullptr == FindSound(_strKey));

	CSound* pSound = new CSound;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound �ε� ����!!!", L"���ҽ� �ε� ����", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map �� ���
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}