
#include "COptMap.h"
//#include "OptionManager.h"



	
COptionElem & COptMap::operator[] (const std::string & keystr) { return _optmap[keystr]; }
COptionElem & COptMap::operator[] (std::string && keystr) { return _optmap[std::move(keystr)]; }

COptionElem & COptMap::at(const std::string & keystr) { return _optmap.at(keystr); }
COptionElem COptMap::at(const std::string & keystr) const { return _optmap.at(keystr); }

bool COptMap::exist(const std::string & keystr) const { return _optmap.count(keystr) > 0; }

Itype & COptMap::GetIntAt(const std::string & keystr) { return _optmap.at(keystr).GetInt(); }
Itype COptMap::GetIntAt(const std::string & keystr) const { return _optmap.at(keystr).GetInt(); }

U_Itype & COptMap::GetUIntAt(const std::string & keystr) { return _optmap.at(keystr).GetUInt(); }
U_Itype COptMap::GetUIntAt(const std::string & keystr) const { return _optmap.at(keystr).GetUInt(); }

Ftype & COptMap::GetFloatAt(const std::string & keystr) { return _optmap.at(keystr).GetFloat(); }
Ftype COptMap::GetFloatAt(const std::string & keystr) const { return _optmap.at(keystr).GetFloat(); }

Chtype & COptMap::GetCharAt(const std::string & keystr) { return _optmap.at(keystr).GetChar(); }
Chtype COptMap::GetCharAt(const std::string & keystr) const { return _optmap.at(keystr).GetChar(); }

U_Chtype & COptMap::GetUCharAt(const std::string & keystr) { return _optmap.at(keystr).GetUChar(); }
U_Chtype COptMap::GetUCharAt(const std::string & keystr) const { return _optmap.at(keystr).GetUChar(); }

Btype & COptMap::GetBoolAt(const std::string & keystr) { return _optmap.at(keystr).GetBool(); }
Btype COptMap::GetBoolAt(const std::string & keystr) const { return _optmap.at(keystr).GetBool(); }

std::string & COptMap::GetStringAt(const std::string & keystr) { return _optmap.at(keystr).GetString(); }
std::string COptMap::GetStringAt(const std::string & keystr) const { return _optmap.at(keystr).GetString(); }

std::vector<COptionElem> & COptMap::GetVectorAt(const std::string & keystr) { return _optmap.at(keystr).GetVector(); }
std::vector<COptionElem> COptMap::GetVectorAt(const std::string & keystr) const { return _optmap.at(keystr).GetVector(); }

COptMap & COptMap::GetMapAt(const std::string & keystr) { return _optmap.at(keystr).GetMap(); }
COptMap COptMap::GetMapAt(const std::string & keystr) const { return _optmap.at(keystr).GetMap(); };
