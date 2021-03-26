#pragma once

#include <map>
#include "OptionManager.h"


namespace OptTypes {
	using Itype = long long;
	using U_Itype = unsigned long long;

	using Ftype = double;

	using Chtype = char;
	using U_Chtype = unsigned char;

	using Btype = bool;
}


using namespace OptTypes;

class COptionElem;

class COptMap
{
public:
	COptMap() {}
	COptMap(const COptMap & rhs) : _optmap(rhs._optmap) {}
	COptMap(COptMap && rhs) : _optmap(std::move(rhs._optmap)) {}

	COptMap & operator=(const COptMap & rhs) { this->_optmap = rhs._optmap; return *this; }
	COptMap & operator=(COptMap && rhs) { this->_optmap = std::move(rhs._optmap); return *this; }

	COptionElem & operator[] (const std::string & keystr);
	COptionElem & operator[] (std::string && keystr);

	COptionElem & at(const std::string & keystr);
	COptionElem at(const std::string & keystr) const;

	bool exist(const std::string & keystr) const;

	Itype & GetIntAt(const std::string & keystr);
	Itype GetIntAt(const std::string & keystr) const;

	U_Itype & GetUIntAt(const std::string & keystr);
	U_Itype GetUIntAt(const std::string & keystr) const;

	Ftype & GetFloatAt(const std::string & keystr);
	Ftype GetFloatAt(const std::string & keystr) const;

	Chtype & GetCharAt(const std::string & keystr);
	Chtype GetCharAt(const std::string & keystr) const;

	U_Chtype & GetUCharAt(const std::string & keystr);
	U_Chtype GetUCharAt(const std::string & keystr) const;

	Btype & GetBoolAt(const std::string & keystr);
	Btype GetBoolAt(const std::string & keystr) const;

	std::string & GetStringAt(const std::string & keystr);
	std::string GetStringAt(const std::string & keystr) const;

	std::vector<COptionElem> & GetVectorAt(const std::string & keystr);
	std::vector<COptionElem> GetVectorAt(const std::string & keystr) const;

	COptMap & GetMapAt(const std::string & keystr);
	COptMap GetMapAt(const std::string & keystr) const;

	virtual ~COptMap() {}

private:
	std::map <std::string, COptionElem> _optmap;
};
