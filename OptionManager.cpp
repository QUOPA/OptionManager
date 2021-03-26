#include "stdafx.h"
#include "OptionManager.h"



COptionElem & COptionElem::operator=(const COptionElem & rhs)
{
	CopyNonMoves(rhs);
	switch (rhs._opType)
	{
	case _VT_STR:
		this->_str = rhs._str;
		break;
	case _VT_VEC:
		this->_vec = rhs._vec;
		break;
	case _VT_MAP:
		this->_pmap.reset( new COptMap(*rhs._pmap));
		break;
	}
	return *this;
}

COptionElem & COptionElem::operator=(COptionElem && rhs)
{
	CopyNonMoves(rhs);
	switch (rhs._opType)
	{
	case _VT_STR:
		this->_str = std::move(rhs._str);
		break;
	case _VT_VEC:
		this->_vec = std::move(rhs._vec);
		break;
	case _VT_MAP:
		this->_pmap.reset(new COptMap(*rhs._pmap));
		break;
	}
	return *this;
}

std::string COptionElem::type()
{
	std::string retstr;
	switch (_opType)
	{
	case _VT_I:
		if (_bUnsign)
			retstr = "unsigned integer";
		else
			retstr = "integer";
		break;
	case _VT_F:
		retstr = "floating number";
		break;
	case _VT_C:
		if (_bUnsign)
			retstr = "unsigned charracter";
		else
			retstr = "character";
		break;
	case _VT_B:
		retstr = "boolean";
		break;
	case _VT_STR:
		retstr = "string";
		break;
	case _VT_VEC:
		retstr = "vector";
		break;
	case _VT_MAP:
		retstr = "map";
		break;
	}
	return retstr;
}

// --- Map Type ---
// Ctors
COptionElem::COptionElem(const COptMap & rhs) : _opType(_VT_MAP) { _pmap.reset(new COptMap(rhs)); }
//COptionElem::COptionElem(COptMap && rhs) : _opType(_VT_MAP), _map(std::move(rhs)) {}

// Converter
COptionElem::operator COptMap() const { return GetMap(); }	//Converter

// Assingment
COptionElem& COptionElem::operator=(const COptMap & rhs) { SetMap(rhs); return *this; }
//inline COptionElem& COptionElem::operator=(COptMap && rhs) { SetMap(std::move(rhs)); return *this; }

//Setter
void COptionElem::SetMap(const COptMap & rhs) { _opType = _VT_MAP, _pmap.reset(new COptMap(rhs)); }
//inline void COptionElem::SetMap(COptMap && rhs) { _opType = _VT_MAP, _map = std::move(rhs); }

// Getter
COptMap & COptionElem::GetMap() { assert(_opType == _VT_MAP); return *_pmap; }
COptMap COptionElem::GetMap() const { assert(_opType == _VT_MAP); return *_pmap; }


COptionElem & COptionElem::at(const std::string & keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but at(const std::string &) is called");
	return _pmap->at(keystr); 
}

COptionElem COptionElem::at(const std::string & keystr) const
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but at (const std::string &) const is called");
	return _pmap->at(keystr); 
}

COptionElem & COptionElem::operator[](const std::string & keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but operator[] (const std::string &) is called");
	return _pmap->operator[](keystr); 
}

COptionElem & COptionElem::operator[](std::string && keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but operator[] (std::string &&) is called");
	return _pmap->operator[](std::move(keystr)); 
}

COptionElem & COptionElem::at(size_t idx)
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but at(size_t) is called");
	return _vec.at(idx); 
}

COptionElem COptionElem::at(size_t idx) const
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but at(size_t) const is called");
	return _vec.at(idx); 
}

COptionElem & COptionElem::operator[](size_t idx)
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but operator[] (size_t) is called");
	return _vec[idx]; 
}

COptionElem COptionElem::operator[](size_t idx) const
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but operator[] (size_t) const is called");
	return _vec[idx]; 
}

void COptionElem::CopyNonMoves(const COptionElem & rhs)
{
	this->_opType = rhs._opType;
	this->_bUnsign = rhs._bUnsign;
	switch (rhs._opType)
	{
	case _VT_I:
		if (_bUnsign)
			this->_vtOpt._ul = rhs._vtOpt._ul;
		else
			this->_vtOpt._l = rhs._vtOpt._l;
		break;
	case _VT_F:
		this->_vtOpt._f = rhs._vtOpt._f;
		break;
	case _VT_C:
		if (_bUnsign)
			this->_vtOpt._uc = rhs._vtOpt._uc;
		else
			this->_vtOpt._c = rhs._vtOpt._c;
		break;
	case _VT_B:
		this->_vtOpt._b = rhs._vtOpt._b;
		break;
	}
}

