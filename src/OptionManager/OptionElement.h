#pragma once

/*!
 * 여러 타입의 데이터를 공통된 인터페이스로 Set/Get할 수 있는 COptimElem Class와
 * COptimElem Class를 Map형태로 사용할 수 있는 COptMap을 지원함.
 * Version 0.3.0
 */ 



#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>

#include "OptionMap.h"
#include "OptionTypes.h"
#include "OptionUtilFns.h"

// unsigned <-> signed implicit은 허용한다. 

//class COptionElem;

// 아래 Define 내용 Constructor, Detter, 
#define _GEN_COPT_CTOR_(_T1, _T2, _TE, _UNSIG) COptionElem(_T1  i) : _opType(_TE), _bUnsign(_UNSIG), _vtOpt(static_cast<_T2>(i))  {}
#define _GEN_COPT_CONVERTER_(_T1, _TE, _VT)  operator _T1() const { assert(_opType == _TE);  return static_cast<_T1>(_vtOpt._VT); }
#define _GEN_COPT_ASSIGN_(_T1, _T2, _TE, _VT, _UNSIG) COptionElem & operator= (const _T1 & rhs) { deleteDynMemoryIfExist(); _opType = _TE; _bUnsign =_UNSIG ;  _vtOpt._VT = static_cast<_T2>(rhs); return *this; }

// 아래 Define을 쓰면 생성되는 것들
#define _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, _T2, _TE, _VT, _UNSIG) _GEN_COPT_CTOR_(_T1, _T2, _TE, _UNSIG) \
_GEN_COPT_CONVERTER_(_T1, _TE, _VT) \
_GEN_COPT_ASSIGN_(_T1, _T2, _TE, _VT, _UNSIG)  


#define _GEN_COPT_IN_OUT_PAIR_IType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Itype, _VT_I , _l, false)  \
void SetInt(_T1 val) {deleteDynMemoryIfExist(); _opType = _VT_I;  _vtOpt._l = static_cast<Itype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_UIType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, U_Itype,  _VT_I ,_ul, true)  \
void SetUInt(_T1 val) {deleteDynMemoryIfExist(); _opType = _VT_I; _bUnsign = true;  _vtOpt._ul = static_cast<U_Itype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_FType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Ftype, _VT_F, _f, false)  \
void SetFloat(_T1 val) {deleteDynMemoryIfExist(); _opType = _VT_F;  _vtOpt._f = static_cast<Ftype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_CType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Chtype, _VT_C, _c, false) \
void SetChar(_T1 val) {deleteDynMemoryIfExist(); _opType = _VT_C;  _vtOpt._c = static_cast<Chtype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_UCType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, U_Chtype, _VT_C, _uc, true) \
void SetUChar(_T1 val) {deleteDynMemoryIfExist(); _opType = _VT_C; _bUnsign = true;  _vtOpt._uc = static_cast<U_Chtype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_BType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Btype, _VT_B, _b, false) \
void SetBool(_T1 val) {deleteDynMemoryIfExist(); _opType = _VT_B;  _vtOpt._b = static_cast<Btype>(val); }

namespace OptTypes {
	using Itype = long long;
	using U_Itype = unsigned long long;

	using Ftype = double;

	using Chtype = char;
	using U_Chtype = unsigned char;

	using Btype = bool;
}

// 아래 정의된 Type에 대해서 사용할 수 있습니다. 
// enum을 입 출력으로 사용하기 위해 int로 명시적으로 변환 후 입력하고, 명시적으로 COptionElem을 int로 변환 후 enum에 넣어주어야 합니다.

using namespace OptTypes;




class COptMap;

class COptionElem
{
public:
	enum OpType
	{
		_UNINITIALIZED = 0,
		_VT_I = 1,
		_VT_F = 2,
		_VT_C = 3,
		_VT_B = 4,

		_VT_STR = 5,
		_VT_VEC = 6,
		_VT_MAP = 7
	};


	// Uninitialized Default
	COptionElem() : _opType(_UNINITIALIZED), _bUnsign(false) {}

	// Copy & move Ctor, Assignment, Dtor
	COptionElem(const COptionElem& rhs) { *this = rhs; }
	COptionElem(COptionElem&& rhs) { *this = std::move(rhs); }

	COptionElem& operator=(const COptionElem& rhs);
	COptionElem& operator=(COptionElem&& rhs);

	virtual ~COptionElem() { deleteDynMemoryIfExist(); }


	// Integers
	_GEN_COPT_IN_OUT_PAIR_IType(int)
		_GEN_COPT_IN_OUT_PAIR_IType(long)
		_GEN_COPT_IN_OUT_PAIR_IType(long long)
		_GEN_COPT_IN_OUT_PAIR_IType(short)
		Itype& GetInt() { assert(_opType == _VT_I);  return _vtOpt._l; }
	const Itype& GetInt() const { assert(_opType == _VT_I);  return _vtOpt._l; }

	// Unsigned Integers
	_GEN_COPT_IN_OUT_PAIR_UIType(unsigned int)
		_GEN_COPT_IN_OUT_PAIR_UIType(unsigned long)
		_GEN_COPT_IN_OUT_PAIR_UIType(unsigned long long)
		_GEN_COPT_IN_OUT_PAIR_UIType(unsigned short)
		U_Itype& GetUInt() { assert(_opType == _VT_I);  return _vtOpt._ul; }
	const U_Itype& GetUInt() const { assert(_opType == _VT_I);  return _vtOpt._ul; }

	// Floating Types
	_GEN_COPT_IN_OUT_PAIR_FType(float)
		_GEN_COPT_IN_OUT_PAIR_FType(double)
		Ftype& GetFloat() { assert(_opType == _VT_F);  return _vtOpt._f; }
	const Ftype& GetFloat() const { assert(_opType == _VT_F);  return _vtOpt._f; }

	// Char Types
	_GEN_COPT_IN_OUT_PAIR_CType(char)
		Chtype& GetChar() { assert(_opType == _VT_C);  return _vtOpt._c; }
	const Chtype& GetChar() const { assert(_opType == _VT_C);  return _vtOpt._c; }

	// Unsigned Char type
	_GEN_COPT_IN_OUT_PAIR_UCType(unsigned char)
		U_Chtype& GetUChar() { assert(_opType == _VT_C);  return _vtOpt._uc; }
	const U_Chtype& GetUChar() const { assert(_opType == _VT_C);  return _vtOpt._uc; }

	// Bool Type
	_GEN_COPT_IN_OUT_PAIR_BType(bool)
		Btype& GetBool() { assert(_opType == _VT_B);  return _vtOpt._b; }
	const Btype& GetBool() const { assert(_opType == _VT_B);  return _vtOpt._b; }

	// --- String Type ---
	// CTor
	// COptionElem(const char szStr []) : _opType(_VT_STR), _str(szStr) {}

	COptionElem(const char* szStr)
		: _opType(_VT_STR), _vtOpt(new std::string(szStr)) {}

	COptionElem(const std::string& str)
		: _opType(_VT_STR), _vtOpt(new std::string(str)) {}

	COptionElem(std::string&& str)
		: _opType(_VT_STR), _vtOpt(new std::string(std::move(str))) {}


	// Convertor
	operator std::string() const { return GetString(); }
	// Assinment
	COptionElem& operator= (const char* szStr) { SetString(szStr); return *this; }

	COptionElem& operator= (const std::string& str) { SetString(str); return *this; }

	COptionElem& operator= (std::string&& str) { SetString(std::move(str)); return *this; }


	// Setter
	void SetString(const char* szStr)
	{
		deleteDynMemoryIfExist();
		_opType = _VT_STR;
		_vtOpt._pstr = new std::string(szStr);
	}
	void SetString(const std::string& str)
	{
		deleteDynMemoryIfExist();
		_opType = _VT_STR;
		_vtOpt._pstr = new std::string(str);
	}
	void SetString(std::string&& str)
	{
		deleteDynMemoryIfExist();
		_opType = _VT_STR;
		_vtOpt._pstr = new std::string(std::move(str));
	}

	// Getter
	std::string& GetString() { assert(_opType == _VT_STR); return *_vtOpt._pstr; }
	const std::string& GetString() const { assert(_opType == _VT_STR); return *_vtOpt._pstr; }

	// --- Vector Type ---
	// CTor
	COptionElem(const std::vector<COptionElem>& vec)
		: _opType(_VT_VEC), _vtOpt(new std::vector<COptionElem>(vec)) {}
	COptionElem(std::vector<COptionElem>&& vec)
		: _opType(_VT_VEC), _vtOpt(new std::vector<COptionElem>(std::move(vec))) {}

	template<typename T>
	COptionElem(const std::vector<T>& vec) { SetVector<T>(vec); }

	template<typename T>
	COptionElem(std::vector<T>&& vec) { SetVector<T>(vec); }



	// Converter
	operator std::vector<COptionElem>() const { return GetVector(); }	//Converter

	template<typename T>
	operator std::vector<T>() const { return GetVectorWithType<T>(); }

	// Assingment
	COptionElem& operator=(const std::vector<COptionElem>& vec) { SetVector(vec); return *this; }
	COptionElem& operator=(std::vector<COptionElem>&& vec) { SetVector(std::move(vec)); return *this; }

	template<typename T>
	COptionElem& operator=(const std::vector<T>& vec) { SetVector<T>(vec); return *this; }

	// Setter
	void SetVector(const std::vector<COptionElem>& vec)
	{
		deleteDynMemoryIfExist();
		_opType = _VT_VEC;
		_vtOpt._pvec = new std::vector<COptionElem>(vec);
	}
	void SetVector(std::vector<COptionElem>&& vec)
	{
		deleteDynMemoryIfExist();
		_opType = _VT_VEC;
		_vtOpt._pvec = new std::vector<COptionElem>(std::move(vec));
	}

	template <typename TargetType, typename T>
	void SetVectorWithType(const std::vector<T>& vec)		// for enums
	{
		deleteDynMemoryIfExist();
		_opType = _VT_VEC;
		int vecSize = vec.size();

		_vtOpt._pvec = new std::vector<COptionElem>(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			_vtOpt._pvec->operator[](i) = static_cast<TargetType>(vec[i]);
		}
	}

	template <typename T>
	void SetVector(const std::vector<T>& vec)
	{
		deleteDynMemoryIfExist();
		_opType = _VT_VEC;
		int vecSize = vec.size();

		_vtOpt._pvec = new std::vector<COptionElem>(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			_vtOpt._pvec->operator[](i) = vec[i];
		}
	}

	// Getter
	std::vector<COptionElem>& GetVector() { assert(_opType == _VT_VEC); return *_vtOpt._pvec; }
	const std::vector<COptionElem>& GetVector() const { assert(_opType == _VT_VEC); return *_vtOpt._pvec; }

	template<typename T>
	std::vector<T> GetVectorWithType() const
	{
		assert(_opType == _VT_VEC);
		std::vector<T> vecTmp;
		int vecSize = _vtOpt._pvec->size();

		vecTmp.resize(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			// Vector can be implicetly converted to the vector of something that COptionElem object could be implicitly converted.
			// When we want to return vector of ENUM, the there is no direct way to convert vector<COptionElem> into vector<ENUM>.
			// rather vector<COptionElem> -> vector<enum> -> vector<ENUM>.
			vecTmp[i] = _vtOpt._pvec->operator[](i);
		}
		return vecTmp;
	}

	std::string typestr() const;
	OpType type() const { return _opType; }
	bool isunsigned() const { return _bUnsign; }

	// --- Map Type ---
	// Ctors

	COptionElem(const COptMap& rhs);
	COptionElem(COptMap&& rhs);

	template<typename T>
	COptionElem(const std::map<std::string, T>& rhs);


	// Converter
	operator COptMap() const;	//Converter

// 	template<typename T>
// 	operator std::map<std::string, T>() const;

	// Assingment

	COptionElem& operator=(const COptMap& rhs);
	COptionElem& operator=(COptMap&& rhs);

	template<typename T>
	COptionElem& operator=(const std::map<std::string, T>& rhs);

	//Setter
	void SetMap(const COptMap& rhs);
	void SetMap(COptMap&& rhs);

	template <typename T>
	void SetMap(const std::map<std::string, T>& rhs);

	// Getter
	COptMap& GetMap();
	const COptMap& GetMap() const;

	// 	template<typename T>
	// 	std::map<std::string, T> GetMapWithType() const;


		// for map

	COptionElem& at(const std::string& keyval);
	const COptionElem& at(const std::string& keyval) const;

	COptionElem& operator[] (const std::string& keyval);
	const COptionElem& operator[] (const std::string& keyval) const;


	COptionElem& operator[] (const char* keyval) { return this->operator[](std::string(keyval)); }
	const COptionElem& operator[] (const char* keyval) const { return this->operator[](std::string(keyval)); }



// 	// for vector
// 	COptionElem& at(size_t idx);
// 	const COptionElem& at(size_t idx) const;
// 
// 	COptionElem& operator[] (size_t idx);
// 	const COptionElem& operator[] (size_t idx) const;



private:



	void CopyNonMoves(const COptionElem& rhs);

	void deleteDynMemoryIfExist();

	OpType _opType;
	
	bool _bUnsign;

	union OpElem
	{
		OpElem() {}
		OpElem(Itype l) : _l(l) {}
		OpElem(U_Itype ul) : _ul(ul) {}

		OpElem(Ftype f) : _f(f) {}
		OpElem(Chtype c) : _c(c) {}
		OpElem(U_Chtype uc) : _uc(uc) {}

		OpElem(Btype b) : _b(b) {}

		OpElem(std::string* rhspstr) : _pstr(rhspstr) {}
		OpElem(std::vector<COptionElem>* rhspvec) : _pvec(rhspvec) {}
		OpElem(COptMap* rhspmap) : _pmap(rhspmap) {}


		Itype _l;		
		U_Itype _ul;

		Ftype _f;		
		Chtype _c;		
		U_Chtype _uc;

		Btype _b;

		std::string* _pstr;
		std::vector<COptionElem>* _pvec;
		COptMap* _pmap;
		
	} _vtOpt;

	friend std::ostream & operator<<(std::ostream& os, const COptionElem& Opt);
};

template<typename T>
inline COptionElem::COptionElem(const std::map<std::string, T> & rhs) { SetMap<T>(rhs);  }

// template<typename T>
// COptionElem::operator std::map<std::string, T>() const { return GetMapWithType<T>(); }

template<typename T>
COptionElem& COptionElem::operator=(const std::map<std::string, T> & rhs) { SetMap<T>(rhs); return *this; }

template <typename T>
void COptionElem::SetMap(const std::map<std::string, T>& rhs)
{
	deleteDynMemoryIfExist();
	_opType = _VT_MAP;
	_vtOpt._pmap = new COptMap(rhs);
}
 
// template<typename T>
// std::map<std::string, T> COptionElem::GetMapWithType() const
// {
// 	assert(_opType == _VT_MAP);
// 	std::map<std::string, T> mapTmp;
// 	
// 	auto it = _vtOpt._pmap->_optmap.begin();
// 	auto itEnd = _vtOpt._pmap->_optmap.end();
// 
// 	for (; it != itEnd; ++it)
// 	{
// 		// OptMap can be implicetly converted to the map with value type that COptionElem object could be implicitly converted.
// 		// When we want to return map with value type of ENUM, there is no direct way to convert OptMap into std::map<std::string, ENUM>.
// 		// rather OptMap -> std::map<std::string, int> -> std::map<std::string, ENUM>.
// 		
// 		
// 		mapTmp[it->first] = _pmap->at(i).first;
// 		mapTmp[i].second = static_cast<T>(_pmap->at(i).second);
// 	}
// 	return mapTmp;
// }

std::ostream& operator<<(std::ostream& os, const COptionElem& Opt);

