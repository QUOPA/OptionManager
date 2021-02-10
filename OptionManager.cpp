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
		this->_map = rhs._map;
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
		this->_map = std::move(rhs._map);
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

