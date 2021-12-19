#pragma once

#include <map>
#include "OptionElement.h"
#include "OptionTypes.h"



using namespace OptTypes;

class COptionElem;

class COptMap
{
public:
	COptMap() {}
	
	// copy, assign
	COptMap(const COptMap & rhs) : _optmap(rhs._optmap) {}
	COptMap(COptMap && rhs) : _optmap(std::move(rhs._optmap)) {}

	template <typename T>
	COptMap(const std::map<std::string, T>& rhs) 
	{
		_optmap.clear();
		auto it = rhs.begin();
		auto itEnd = rhs.end();

		for (; it != itEnd; ++it)
		{
			_optmap[it->first] = it->second;
		}
	}

	template <typename T>
	COptMap(std::map<std::string, T>&& rhs)
	{
		_optmap.clear();
		auto it = rhs.begin();
		auto itEnd = rhs.begin();

		for (; it != itEnd; ++it)
		{
			_optmap[it->first] = std::move(it->second);
		}
	}



	COptMap & operator=(const COptMap & rhs) { this->_optmap = rhs._optmap; return *this; }
	COptMap & operator=(COptMap && rhs) { this->_optmap = std::move(rhs._optmap); return *this; }



	// element access
	COptionElem & operator[] (const std::string & keystr);
	const COptionElem & operator[] (const std::string& keystr) const;

	COptionElem & at(const std::string & keystr);
	const COptionElem & at(const std::string & keystr) const;

	// other utility functions
	bool Exist(const std::string& keystr) const;
	
	void Erase(const std::string& keystr) { _optmap.erase(keystr); };
	
	void Clear() { _optmap.clear(); };

	size_t Size() { return _optmap.size(); };

	std::vector<std::string> GetKeyVector();
	std::vector<COptionElem> GetValVector();
	std::pair <std::vector<std::string>, std::vector<COptionElem> > GetKeyValVectors();

	std::map <std::string, COptionElem>::iterator Begin() { return _optmap.begin(); }
	std::map <std::string, COptionElem>::iterator End() { return _optmap.end(); }

	std::map <std::string, COptionElem>::const_iterator cBegin() { return _optmap.cbegin(); }
	std::map <std::string, COptionElem>::const_iterator cEnd() { return _optmap.cend(); }

	// to be updated : merge

	// Type Specific Retrive

	Itype & GetIntAt(const std::string & keystr);
	const Itype & GetIntAt(const std::string & keystr) const;

	U_Itype & GetUIntAt(const std::string & keystr);
	const U_Itype & GetUIntAt(const std::string & keystr) const;

	Ftype & GetFloatAt(const std::string & keystr);
	const Ftype & GetFloatAt(const std::string & keystr) const;

	Chtype & GetCharAt(const std::string & keystr);
	const Chtype & GetCharAt(const std::string & keystr) const;

	U_Chtype & GetUCharAt(const std::string & keystr);
	const U_Chtype & GetUCharAt(const std::string & keystr) const;

	Btype & GetBoolAt(const std::string & keystr);
	const Btype & GetBoolAt(const std::string & keystr) const;

	std::string & GetStringAt(const std::string & keystr);
	const std::string & GetStringAt(const std::string & keystr) const;

	std::vector<COptionElem> & GetVectorAt(const std::string & keystr);
	const std::vector<COptionElem> & GetVectorAt(const std::string & keystr) const;

	COptMap & GetMapAt(const std::string & keystr);
	const COptMap & GetMapAt(const std::string & keystr) const;

	virtual ~COptMap() {}

private:
	std::map <std::string, COptionElem> _optmap;
	friend class COptionElem;
};
