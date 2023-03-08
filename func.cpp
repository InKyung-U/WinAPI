#include "pch.h"
#include "func.h"

#include "CEventMgr.h"
#include "CObj.h"
#include "CForcePoint.h"

void CreateObject(CObj* _pNewObj, EOBJ_TYPE _eType, Vec2 _vPos)
{
	_pNewObj->SetPos(_vPos);

	tEventInfo info = {};
	info.eType = EEVENT_TYPE::CREATE_OBJ;
	info.lParam = (DWORD_PTR)_pNewObj;
	info.wParam = (DWORD_PTR)_eType;

	CEventMgr::GetInst()->AddEvent(info);
}

void CreateForce(EOBJ_TYPE _eTargetType, Vec2 _vPos, float _fForce, float _fDistance, float _fLifeTime)
{
	CForcePoint* pForceObj = new CForcePoint;

	pForceObj->SetForce(_fForce);
	pForceObj->SetTargetType(_eTargetType);
	pForceObj->SetDistance(_fDistance);
	pForceObj->SetLifeTime(_fLifeTime);

	CreateObject(pForceObj, EOBJ_TYPE::FORCE, _vPos);
}


void DeleteObject(CObj* _pTargetObj)
{
	tEventInfo info = {};
	info.eType = EEVENT_TYPE::DELETE_OBJ;
	info.lParam = (DWORD_PTR)_pTargetObj;	

	CEventMgr::GetInst()->AddEvent(info);
}

void ChangeStage(ESTAGE_TYPE _eNext)
{
	tEventInfo info = {};
	info.eType = EEVENT_TYPE::STAGE_CHANGE;
	info.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(info);
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	const wchar_t* pStr = _str.c_str();

	size_t iLen = _str.length();

	// 문자의 길이를 정수로 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// 문자 저장
	fwrite(pStr, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	wchar_t szData[256] = {};
	fread(szData, sizeof(wchar_t), iLen, _pFile);

	_str = szData;
}

Vec2 GetRotateVec(Vec2 _vDir, float _angle)
{
	return Vec2(cosf(_angle) * _vDir.x - sinf(_angle) * _vDir.y, sinf(_angle) * _vDir.x + cosf(_angle) * _vDir.y);
}
