#include "VariantElement.h"



CVariantElem & CVariantElem::operator=(const CVariantElem & rhs)
{
	deleteDynMemoryIfExist();
	CopyNonMoves(rhs);
	switch (rhs._opType)
	{
	case _VT_STR:
		this->_vtOpt._pstr = new std::string(*rhs._vtOpt._pstr);
		break;
	case _VT_VEC:
		this->_vtOpt._pvec = new std::vector<CVariantElem>(*rhs._vtOpt._pvec);
		break;
	case _VT_MAP:
		this->_vtOpt._pmap = new COptMap(*rhs._vtOpt._pmap);
		break;
	}
	return *this;
}

CVariantElem & CVariantElem::operator=(CVariantElem && rhs)
{
	deleteDynMemoryIfExist();
	CopyNonMoves(rhs);
	switch (rhs._opType)
	{
	case _VT_STR:
		this->_vtOpt._pstr = new std::string(std::move(*rhs._vtOpt._pstr));
		break;
	case _VT_VEC:
		this->_vtOpt._pvec = new std::vector<CVariantElem>(std::move(*rhs._vtOpt._pvec) );
		break;
	case _VT_MAP:
		this->_vtOpt._pmap = new COptMap(std::move(*rhs._vtOpt._pmap));
		break;
	}
	return *this;
}

std::string CVariantElem::typestr() const
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
CVariantElem::CVariantElem(const COptMap & rhs) : _opType(_VT_MAP), _vtOpt(new COptMap(rhs)) {}

CVariantElem::CVariantElem(COptMap&& rhs) : _opType(_VT_MAP), _vtOpt(new COptMap(std::move(rhs))) {}

// Converter
CVariantElem::operator COptMap() const { return GetMap(); }	//Converter

// Assingment
CVariantElem& CVariantElem::operator=(const COptMap & rhs) { SetMap(rhs); return *this; }
CVariantElem& CVariantElem::operator=(COptMap && rhs) { SetMap(std::move(rhs)); return *this; }

//Setter
void CVariantElem::SetMap(const COptMap& rhs) { deleteDynMemoryIfExist(); _opType = _VT_MAP; _vtOpt._pmap = new COptMap(rhs); }
void CVariantElem::SetMap(COptMap && rhs) { deleteDynMemoryIfExist(); _opType = _VT_MAP; _vtOpt._pmap = new COptMap(std::move(rhs)); }

// Getter
COptMap & CVariantElem::GetMap() { assert(_opType == _VT_MAP); return *_vtOpt._pmap; }
const COptMap & CVariantElem::GetMap() const { assert(_opType == _VT_MAP); return *_vtOpt._pmap; }

CVariantElem & CVariantElem::at(const std::string & keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but at(const std::string &) is called");
	return _vtOpt._pmap->at(keystr);
}

const CVariantElem & CVariantElem::at(const std::string & keystr) const
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but at (const std::string &) const is called");
	return _vtOpt._pmap->at(keystr);
}

CVariantElem & CVariantElem::operator[](const std::string & keystr)
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but operator[] (const std::string &) is called");
	return _vtOpt._pmap->operator[](keystr);
}

const CVariantElem & CVariantElem::operator[](const std::string& keystr) const
{
	if (_opType != _VT_MAP)
		throw std::out_of_range("COptionElem's type is not a map but operator[] (std::string &&) is called");
	return _vtOpt._pmap->operator[](keystr);
}

// CVariantElem & CVariantElem::at(size_t idx)
// {
// 	if (_opType != _VT_VEC)
// 		throw std::out_of_range("CVariantElem's type is not a vector but at(size_t) is called");
// 	return _vtOpt._pvec->at(idx);
// }
// 
// const CVariantElem & CVariantElem::at(size_t idx) const
// {
// 	if (_opType != _VT_VEC)
// 		throw std::out_of_range("CVariantElem's type is not a vector but at(size_t) const is called");
// 	return _vtOpt._pvec->at(idx);
// }
// 
// CVariantElem & CVariantElem::operator[](size_t idx)
// {
// 	if (_opType != _VT_VEC)
// 		throw std::out_of_range("CVariantElem's type is not a vector but operator[] (size_t) is called");
// 	return _vtOpt._pvec->operator[](idx);
// }
// 
// const CVariantElem & CVariantElem::operator[](size_t idx) const
// {
// 	if (_opType != _VT_VEC)
// 		throw std::out_of_range("CVariantElem's type is not a vector but operator[] (size_t) const is called");
// 	return _vtOpt._pvec->operator[](idx);
// }

void CVariantElem::CopyNonMoves(const CVariantElem & rhs)
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

void CVariantElem::deleteDynMemoryIfExist()
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


std::ostream& operator<<(std::ostream& os, const CVariantElem& Opt)
{
	os << "(" << Opt.typestr() << ")";

	std::string retstr;
	switch (Opt.type())
	{
	case CVariantElem::_VT_I:
		if (Opt.isunsigned())
			os << Opt._vtOpt._ul;
		else
			os << Opt._vtOpt._l;
		break;
	case CVariantElem::_VT_F:
		os << Opt._vtOpt._f;
		break;
	case CVariantElem::_VT_C:
		if (Opt.isunsigned())
			os << Opt._vtOpt._uc;
		else
			os << Opt._vtOpt._c;
		break;
	case CVariantElem::_VT_B:
		os << Opt._vtOpt._b;
		break;
	case CVariantElem::_VT_STR:
		os << *Opt._vtOpt._pstr;
		break;
	case CVariantElem::_VT_VEC:
		PrintVector(os, *Opt._vtOpt._pvec);
		break;
	case CVariantElem::_VT_MAP:
		PrintVector(os, Opt._vtOpt._pmap->GetKeyVector());
		break;
	default:
		break;
	}

	return os;
}
