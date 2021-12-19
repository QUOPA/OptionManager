#pragma once

#include  <iostream>
#include <vector>

template<typename T>
void PrintVector(std::ostream& os, const std::vector<T>& Opt);



template<typename T>
void PrintVector(std::ostream& os, const std::vector<T>& Opt)
{
	auto it = Opt.begin();
	auto itEnd = Opt.end();

	int elemcnt = 0;
	os << "{";
	for ( ; it != itEnd; ++it)
	{
		if (elemcnt > 0)
			os << ", ";
		
		os << *it;
		++elemcnt;
	}
	os << "}";
}
