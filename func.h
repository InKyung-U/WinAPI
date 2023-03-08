#pragma once

class CObj;
class CForcePoint;

void CreateObject(CObj* _pNewObj, EOBJ_TYPE _eType, Vec2 _vPos);
void CreateForce(EOBJ_TYPE _eTargetType, Vec2 _vPos, float _fForce, float _fDistance, float _fLifeTime);
void DeleteObject(CObj* _pTargetObj);

void ChangeStage(ESTAGE_TYPE _eNext);

void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* _pFile);


Vec2 GetRotateVec(Vec2 _vDir, float _angle);


template<typename T>
void Safe_Del_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

template<typename T, int size>
void Safe_Del_Arr(T(&Arr)[size])
{
	for (int i = 0; i < size; ++i)
	{
		if (nullptr != Arr[i])
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}


template<typename T1, typename T2>
void Safe_Del_Map(map<T1, T2>& _map)
{
	for (auto& pair : _map)
	{
		if (nullptr != pair.second)
		{
			delete pair.second;
		}
	}

	_map.clear();
}