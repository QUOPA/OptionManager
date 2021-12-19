
#include "OptionMap.h"
//#include "OptionManager.h"


COptionElem & COptMap::operator[] (const std::string & keystr) { return _optmap[keystr]; }
const COptionElem & COptMap::operator[](const std::string& keystr) const { return _optmap.at(keystr); }

COptionElem & COptMap::at(const std::string & keystr) { return _optmap.at(keystr); }
const COptionElem & COptMap::at(const std::string & keystr) const { return _optmap.at(keystr); }

bool COptMap::Exist(const std::string & keystr) const { return _optmap.count(keystr) > 0; }

std::vector<std::string> COptMap::GetKeyVector()
{
    std::vector<std::string> retvec(_optmap.size());
    auto it = _optmap.begin();
    auto itEnd = _optmap.end();
    int idx = 0;
    for (; it != itEnd; ++it)
    {
        retvec[idx] = it->first;
        ++idx;
    }
	return retvec;
}


std::vector<COptionElem> COptMap::GetValVector()
{
	std::vector<COptionElem> retvec(_optmap.size());
	auto it = _optmap.begin();
	auto itEnd = _optmap.end();
	int idx = 0;
	for (; it != itEnd; ++it)
	{
		retvec[idx] = it->second;
		++idx;
	}

	return retvec;
}


std::pair<std::vector<std::string>, std::vector<COptionElem>> COptMap::GetKeyValVectors()
{
	std::vector<std::string> keyvec(_optmap.size());
	std::vector<COptionElem> valvec(_optmap.size());
	auto it = _optmap.begin();
	auto itEnd = _optmap.end();
	int idx = 0;
	for (; it != itEnd; ++it)
	{
		keyvec[idx] = it->first;
		valvec[idx] = it->second;
		++idx;
	}
	return std::make_pair(keyvec, valvec);
}



Itype & COptMap::GetIntAt(const std::string & keystr) { return _optmap.at(keystr).GetInt(); }
const Itype & COptMap::GetIntAt(const std::string & keystr) const { return _optmap.at(keystr).GetInt(); }

U_Itype & COptMap::GetUIntAt(const std::string & keystr) { return _optmap.at(keystr).GetUInt(); }
const U_Itype & COptMap::GetUIntAt(const std::string & keystr) const { return _optmap.at(keystr).GetUInt(); }

Ftype & COptMap::GetFloatAt(const std::string & keystr) { return _optmap.at(keystr).GetFloat(); }
const Ftype & COptMap::GetFloatAt(const std::string & keystr) const { return _optmap.at(keystr).GetFloat(); }

Chtype & COptMap::GetCharAt(const std::string & keystr) { return _optmap.at(keystr).GetChar(); }
const Chtype & COptMap::GetCharAt(const std::string & keystr) const { return _optmap.at(keystr).GetChar(); }

U_Chtype & COptMap::GetUCharAt(const std::string & keystr) { return _optmap.at(keystr).GetUChar(); }
const U_Chtype & COptMap::GetUCharAt(const std::string & keystr) const { return _optmap.at(keystr).GetUChar(); }

Btype & COptMap::GetBoolAt(const std::string & keystr) { return _optmap.at(keystr).GetBool(); }
const Btype & COptMap::GetBoolAt(const std::string & keystr) const { return _optmap.at(keystr).GetBool(); }

std::string & COptMap::GetStringAt(const std::string & keystr) { return _optmap.at(keystr).GetString(); }
const std::string & COptMap::GetStringAt(const std::string & keystr) const { return _optmap.at(keystr).GetString(); }

std::vector<COptionElem> & COptMap::GetVectorAt(const std::string & keystr) { return _optmap.at(keystr).GetVector(); }
const std::vector<COptionElem> & COptMap::GetVectorAt(const std::string & keystr) const { return _optmap.at(keystr).GetVector(); }

COptMap & COptMap::GetMapAt(const std::string & keystr) { return _optmap.at(keystr).GetMap(); }
const COptMap & COptMap::GetMapAt(const std::string & keystr) const { return _optmap.at(keystr).GetMap(); };
