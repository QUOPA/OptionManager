
#include "OptionMap.h"
//#include "OptionManager.h"


COptionElem & COptMap::operator[] (const std::string & keystr) { return _optmap[keystr]; }
const COptionElem & COptMap::operator[](const std::string& keystr) const { return _optmap.at(keystr); }

COptionElem & COptMap::at(const std::string & keystr) { return _optmap.at(keystr); }
const COptionElem & COptMap::at(const std::string & keystr) const { return _optmap.at(keystr); }

bool COptMap::Exist(const std::string & keystr) const { return _optmap.count(keystr) > 0; }

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
