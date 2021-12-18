#include "OptionElement.h"



COptionElem & COptionElem::operator=(const COptionElem & rhs)
{
	deleteDynMemoryIfExist();
	CopyNonMoves(rhs);
	switch (rhs._opType)
	{
	case _VT_STR:
		this->_vtOpt._pstr = new std::string(*rhs._vtOpt._pstr);
		break;
	case _VT_VEC:
		this->_vtOpt._pvec = new std::vector<COptionElem>(*rhs._vtOpt._pvec);
		break;
	case _VT_MAP:
		this->_vtOpt._pmap = new COptMap(*rhs._vtOpt._pmap);
		break;
	}
	return *this;
}

COptionElem & COptionElem::operator=(COptionElem && rhs)
{
	deleteDynMemoryIfExist();
	CopyNonMoves(rhs);
	switch (rhs._opType)
	{
	case _VT_STR:
		this->_vtOpt._pstr = new std::string(std::move(*rhs._vtOpt._pstr));
		break;
	case _VT_VEC:
		this->_vtOpt._pvec = new std::vector<COptionElem>(std::move(*rhs._vtOpt._pvec) );
		break;
	case _VT_MAP:
		this->_vtOpt._pmap = new COptMap(std::move(*rhs._vtOpt._pmap));
		break;
	}
	return *this;
}

std::string COptionElem::typestr() const
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
	default :
		retstr = "undefined";
	}
	return retstr;
}

// --- Map Type ---
// Ctors
COptionElem::COptionElem(const COptMap & rhs) : _opType(_VT_MAP), _vtOpt(new COptMap(rhs)) {}

COptionElem::COptionElem(COptMap&& rhs) : _opType(_VT_MAP), _vtOpt(new COptMap(std::move(rhs))) {}

// Converter
COptionElem::operator COptMap() const { return GetMap(); }	//Converter

// Assingment
COptionElem& COptionElem::operator=(const COptMap & rhs) { SetMap(rhs); return *this; }
COptionElem& COptionElem::operator=(COptMap && rhs) { SetMap(std::move(rhs)); return *this; }

//Setter
void COptionElem::SetMap(const COptMap& rhs) { deleteDynMemoryIfExist(); _opType = _VT_MAP; _vtOpt._pmap = new COptMap(rhs); }
void COptionElem::SetMap(COptMap && rhs) { deleteDynMemoryIfExist(); _opType = _VT_MAP; _vtOpt._pmap = new COptMap(std::move(rhs)); }

// Getter
COptMap & COptionElem::GetMap() { assert(_opType == _VT_MAP); return *_vtOpt._pmap; }
const COptMap & COptionElem::GetMap() const { assert(_opType == _VT_MAP); return *_vtOpt._pmap; }

COptionElem & COptionElem::at(const std::string & keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but at(const std::string &) is called");
	return _vtOpt._pmap->at(keystr);
}

const COptionElem & COptionElem::at(const std::string & keystr) const
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but at (const std::string &) const is called");
	return _vtOpt._pmap->at(keystr);
}

COptionElem & COptionElem::operator[](const std::string & keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but operator[] (const std::string &) is called");
	return _vtOpt._pmap->operator[](keystr);
}

const COptionElem & COptionElem::operator[](const std::string& keystr) const
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but operator[] (std::string &&) is called");
	return _vtOpt._pmap->operator[](keystr);
}

COptionElem & COptionElem::at(size_t idx)
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but at(size_t) is called");
	return _vtOpt._pvec->at(idx);
}

const COptionElem & COptionElem::at(size_t idx) const
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but at(size_t) const is called");
	return _vtOpt._pvec->at(idx);
}

COptionElem & COptionElem::operator[](size_t idx)
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but operator[] (size_t) is called");
	return _vtOpt._pvec->operator[](idx);
}

const COptionElem & COptionElem::operator[](size_t idx) const
{
	if (_opType != _VT_VEC)
		throw std::out_of_range("COptionElem's type is not a vector but operator[] (size_t) const is called");
	return _vtOpt._pvec->operator[](idx);
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

void COptionElem::deleteDynMemoryIfExist()
{
	if (_opType == _VT_STR && _vtOpt._pstr != nullptr)
	{
		delete _vtOpt._pstr;
		_vtOpt._pstr = nullptr;
	}
	else if (_opType == _VT_VEC && _vtOpt._pvec != nullptr)
	{
		delete _vtOpt._pvec;
		_vtOpt._pvec = nullptr;
	}
	else if (_opType == _VT_MAP && _vtOpt._pmap != nullptr)
	{
		delete _vtOpt._pmap;
		_vtOpt._pmap = nullptr;
	}

}


std::ostream& operator<<(std::ostream& os, const COptionElem& Opt)
{
	os << "(" << Opt.typestr() << ")";

	std::string retstr;
	switch (Opt.type())
	{
	case COptionElem::_VT_I:
		if (Opt.isunsigned())
			os << Opt._vtOpt._ul;
		else
			os << Opt._vtOpt._l;
		break;
	case COptionElem::_VT_F:
		os << Opt._vtOpt._f;
		break;
	case COptionElem::_VT_C:
		if (Opt.isunsigned())
			os << Opt._vtOpt._uc;
		else
			os << Opt._vtOpt._c;
		break;
	case COptionElem::_VT_B:
		os << Opt._vtOpt._b;
		break;
	case COptionElem::_VT_STR:
		os << *Opt._vtOpt._pstr;
		break;
	case COptionElem::_VT_VEC:
		break;
	case COptionElem::_VT_MAP:
		break;
	default:
		break;
	}

	return os;
}
