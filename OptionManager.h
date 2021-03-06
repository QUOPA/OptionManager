#pragma once

// Version 0.1.0

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// unsigned <-> signed implicit은 허용한다. 

// 아래 Define 내용 Constructor, Detter, 
#define _GEN_COPT_CTOR_(_T1, _T2, _TE, _UNSIG) COptionElem(_T1  i) : _opType(_TE), _bUnsign(_UNSIG), _vtOpt(static_cast<_T2>(i))  {}
#define _GEN_COPT_CONVERTER_(_T1, _TE, _VT)  operator _T1() const { assert(_opType == _TE);  return static_cast<_T1>(_vtOpt._VT); }
#define _GEN_COPT_ASSIGN_(_T1, _T2, _TE, _VT, _UNSIG) COptionElem & operator= (const _T1 & rhs) { _opType = _TE; _bUnsign =_UNSIG ;  _vtOpt._VT = static_cast<_T2>(rhs); return *this; }

// 아래 Define을 쓰면 생성되는 것들
#define _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, _T2, _TE, _VT, _UNSIG) _GEN_COPT_CTOR_(_T1, _T2, _TE, _UNSIG) \
_GEN_COPT_CONVERTER_(_T1, _TE, _VT) \
_GEN_COPT_ASSIGN_(_T1, _T2, _TE, _VT, _UNSIG)  


#define _GEN_COPT_IN_OUT_PAIR_IType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Itype, _VT_I , _l, false)  \
void SetInt(_T1 val) { _opType = _VT_I;  _vtOpt._l = static_cast<Itype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_UIType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, U_Itype,  _VT_I ,_ul, true)  \
void SetUnsignInt(_T1 val) { _opType = _VT_I; _bUnsign = true;  _vtOpt._ul = static_cast<U_Itype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_FType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Ftype, _VT_F, _f, false)  \
void SetFloat(_T1 val) { _opType = _VT_F;  _vtOpt._f = static_cast<Ftype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_CType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Chtype, _VT_C, _c, false) \
void SetChar(_T1 val) { _opType = _VT_C;  _vtOpt._c = static_cast<Chtype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_UCType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, U_Chtype, _VT_C, _uc, true) \
void SetUnsignChar(_T1 val) { _opType = _VT_C; _bUnsign = true;  _vtOpt._uc = static_cast<U_Chtype>(val); }

#define _GEN_COPT_IN_OUT_PAIR_BType(_T1) _GEN_COPT_CTOR_CONVERTER_ASSIGN_(_T1, Btype, _VT_B, _b, false) \
void SetBool(_T1 val) { _opType = _VT_B;  _vtOpt._b = static_cast<Btype>(val); }

class COptionElem;

// 아래 정의된 Type에 대해서 사용할 수 있습니다. 
// enum을 입 출력으로 사용하기 위해 int로 명시적으로 변환 후 입력하고, 명시적으로 COptionElem을 int로 변환 후 enum에 넣어주어야 합니다.
using COptMap = std::map<std::string, COptionElem>;

class COptionElem 
{
public:
	
	// Uninitialized Default
	COptionElem() : _opType(_UNINITIALIZED), _bUnsign(false) {}

	// Copy & move Ctor, Assignment, Dtor
	COptionElem(const COptionElem & rhs) { *this = rhs; }
	COptionElem(COptionElem && rhs) { *this = std::move(rhs); }

	COptionElem & operator=(const COptionElem & rhs);
	COptionElem & operator=(COptionElem && rhs);

	virtual ~COptionElem() {}


	using Itype = long long;
	using U_Itype = unsigned long long;
	
	using Ftype = double;
	
	using Chtype = char;
	using U_Chtype = unsigned char;

	using Btype = bool;

	// Integers
	_GEN_COPT_IN_OUT_PAIR_IType(int)
	_GEN_COPT_IN_OUT_PAIR_IType(long)
	_GEN_COPT_IN_OUT_PAIR_IType(long long)
	_GEN_COPT_IN_OUT_PAIR_IType(short)	
	Itype GetInt() const { assert(_opType == _VT_I);  return _vtOpt._l; }

	// Unsigned Integers
	_GEN_COPT_IN_OUT_PAIR_UIType(unsigned int)
	_GEN_COPT_IN_OUT_PAIR_UIType(unsigned long)
	_GEN_COPT_IN_OUT_PAIR_UIType(unsigned long long)
	_GEN_COPT_IN_OUT_PAIR_UIType(unsigned short)
	U_Itype GetUnsignInt() const { assert(_opType == _VT_I);  return _vtOpt._ul; }

	// Floating Types
	_GEN_COPT_IN_OUT_PAIR_FType(float)
	_GEN_COPT_IN_OUT_PAIR_FType(double)
	Ftype GetFloat() const { assert(_opType == _VT_F);  return _vtOpt._f; }

	// Char Types
	_GEN_COPT_IN_OUT_PAIR_CType(char)
	Chtype GetChar() const { assert(_opType == _VT_C);  return _vtOpt._c; }

	// Unsigned Char type
	_GEN_COPT_IN_OUT_PAIR_UCType(unsigned char)
	U_Chtype GetUnsignChar() const { assert(_opType == _VT_C);  return _vtOpt._uc; }

	// Bool Type
	_GEN_COPT_IN_OUT_PAIR_BType(bool)
	Btype GetBool() const { assert(_opType == _VT_B);  return _vtOpt._b; }

	
	// --- String Type ---
	// CTor
//	COptionElem(const char szStr []) : _opType(_VT_STR), _str(szStr) {}
	COptionElem(const char * szStr) : _opType(_VT_STR), _str(szStr) {}
	COptionElem(const std::string & str) : _opType(_VT_STR), _str(str) {}					
	COptionElem(std::string && str) : _opType(_VT_STR), _str(std::move(str)) {}					
	// Convertor
	operator std::string() const { return GetString(); }									
	// Assinment
	COptionElem& operator= (const char * szStr) { SetString(szStr); return *this; }
	COptionElem& operator= (const std::string & str) { SetString(str); return *this; }					
	COptionElem& operator= (std::string && str) { SetString(std::move(str)); return *this; }
	// Setter
	void SetString(const char * szStr) { _opType = _VT_STR, _str = szStr; }
	void SetString(const std::string & str) { _opType = _VT_STR, _str = str; }				
	void SetString(std::string && str) { _opType = _VT_STR, _str = std::move(str); }		
	// Getter
	std::string GetString() const { assert(_opType == _VT_STR); return _str; }				

	
	// --- Vector Type ---
	// CTor
	COptionElem(const std::vector<COptionElem> & vec) : _opType(_VT_VEC), _vec(vec) {}		
	COptionElem(std::vector<COptionElem> && vec) : _opType(_VT_VEC), _vec(std::move(vec)) {}		
	template<typename T>				
	COptionElem(const std::vector<T> & vec) { SetVector<T>(vec); }
	// Converter
	operator std::vector<COptionElem>() const { return GetVector(); }	//Converter
	template<typename T>
	operator std::vector<T>() const { return GetVector<T>(); }
	// Assingment
	COptionElem& operator=(const std::vector<COptionElem> & vec) { SetVector(vec); return *this; }
	COptionElem& operator=(std::vector<COptionElem> && vec) { SetVector(std::move(vec)); return *this; }
	template<typename T>
	COptionElem& operator=(const std::vector<T> & vec) { SetVector<T>(vec); return *this; }
	//Setter
	void SetVector(const std::vector<COptionElem> & vec ) { _opType = _VT_VEC, _vec = vec; }		
	void SetVector(std::vector<COptionElem> && vec) { _opType = _VT_VEC, _vec = std::move(vec); }	
	template <typename T>
	void SetVectorInt(const std::vector<T> & vec)		// for enums
	{
		_opType = _VT_VEC;
		int vecSize = vec.size();
		_vec.resize(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			Itype nTmp = static_cast<Itype>(vec[i])
			_vec[i] = nTmp;
		}
	}
	template <typename T>
	void SetVector(const std::vector<T> & vec) 
	{
		_opType = _VT_VEC;
		int vecSize = vec.size();
		_vec.resize(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			_vec[i] = vec[i];
		}
	}
	// Getter
	std::vector<COptionElem> GetVector() const { assert(_opType == _VT_VEC); return _vec; }				
	template<typename T>
	std::vector<T> GetVector() const 
	{
		assert(_opType == _VT_VEC);
		std::vector<T> vecTmp;
		int vecSize = _vec.size();

		vecTmp.resize(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			// Vector에 들어있는 COptionElem 클래스가 implicit converting할 수 있는 Type으로만 변환될 수 있습니다.
			// 특히 enum A에 대한 vector를 return하고자할 경우, 개발자는 COptionElem -> int -> A로의 타입 변환이라고 생각하지만
			// 컴파일러에서는 COptionElem --> A로의 변환이 정의되어있지 않기 때문에 int가 중간에 들어가는지 전혀 알 수 없습니다. 
			// 따라서, C++ 표준에서 이렇게 두번의 implicit conversion은 제공하지 않으며, 아래 구문에서 에러 발생 시 해당 사항을 체크하시기 바랍니다.
			vecTmp[i] = static_cast<T>(_vec.at(i));
		}
		return vecTmp;
	}
	
	std::string type();
	


	
	// --- Map Type ---
	// Ctors
	COptionElem(const COptMap & rhs) : _opType(_VT_MAP), _map(rhs) {}
	COptionElem(COptMap && rhs) : _opType(_VT_MAP), _map(std::move(rhs)) {}
	template<typename T>
	COptionElem(const std::map<std::string, T> & rhs) { SetMap<T>(rhs); }
	// Converter
	operator COptMap() const { return GetMap(); }	//Converter
	template<typename T>
	operator std::map<std::string, T>() const { return GetMap<T>(); }
	// Assingment
	COptionElem& operator=(const COptMap & rhs) { SetMap(rhs); return *this; }
	COptionElem& operator=(COptMap && rhs) { SetMap(std::move(rhs)); return *this; }
	template<typename T>
	COptionElem& operator=(const std::map<std::string, T> & rhs) { SetMap<T>(rhs); return *this; }
	//Setter
	void SetMap(const COptMap & rhs) { _opType = _VT_MAP, _map = rhs; }
	void SetMap(COptMap && rhs) { _opType = _VT_MAP, _map = std::move(rhs); }
	template <typename T>
	void SetMap(const std::map<std::string, T> & rhs)
	{
		_opType = _VT_MAP;
		int vecSize = rhs.size();
		_map.resize(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			_map[i].first = rhs.at(i).first;
			_map[i].second = rhs.at(i).second;
		}
	}
	// Getter
	COptMap GetMap() const { assert(_opType == _VT_MAP); return _map; }
	template<typename T>
	std::map<std::string, T> GetMap() const
	{
		assert(_opType == _VT_MAP);
		std::map<std::string, T> mapTmp;
		int vecSize = _map.size();

		mapTmp.resize(vecSize);
		for (int i = 0; i < vecSize; i++)
		{
			// Vector에 들어있는 COptionElem 클래스가 implicit converting할 수 있는 Type으로만 변환될 수 있습니다.
			// 특히 enum A에 대한 vector를 return하고자할 경우, 개발자는 COptionElem -> int -> A로의 타입 변환이라고 생각하지만
			// 컴파일러에서는 COptionElem --> A로의 변환이 정의되어있지 않기 때문에 int가 중간에 들어가는지 전혀 알 수 없습니다. 
			// 따라서, C++ 표준에서 이렇게 두번의 implicit conversion은 제공하지 않으며, 아래 구문에서 에러 발생 시 해당 사항을 체크하시기 바랍니다.
			mapTmp[i].first = _map.at(i).first;
			mapTmp[i].second = static_cast<T>(_map.at(i).second);
		}
		return mapTmp;
	}




private:


	void CopyNonMoves(const COptionElem& rhs);

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
	} _opType;
	
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

		Itype _l;		
		U_Itype _ul;

		Ftype _f;		
		Chtype _c;		
		U_Chtype _uc;

		Btype _b;
	} _vtOpt;

	std::string _str;	
	std::vector<COptionElem> _vec;	
	COptMap _map;

};




