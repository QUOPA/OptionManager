#pragma once

#include "OptionManager/OptionElement.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace OptElemTest 
{

// void IntTypeTest();
// void UIntTypeTest();

void UndefinedTypeTest()
{
	COptionElem Opt;
	std::cout << Opt.typestr() << std::endl;

	COptionElem Opt2 = Opt;
	std::cout << Opt2.typestr() << std::endl;

}

void IntTypeTest()
{
	int a = 3;
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;

	int b = Opt;
	std::cout << b << std::endl;
}

void UIntTypeTest()
{
	unsigned int a = 3;
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;

	unsigned int b = Opt;
	std::cout << b << std::endl;
}

void CharTypeTest()
{
	char a = 'a';
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;

	char b = Opt;
	std::cout << b << std::endl;
}


void UCharTypeTest()
{
	unsigned char a = 'a';
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;

	unsigned char b = Opt;
	std::cout << b << std::endl;
}

void FloatTypeTest()
{
	double a = 3.14;
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;

	double b = Opt;
	std::cout << b << std::endl;
}

void BoolTypeTest()
{
	bool a = true;
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;

	bool b = Opt;
	std::cout << b << std::endl;
}


void StringTypeTest()
{
	std::string a = "abcabc";
	COptionElem Opt(a);
	std::cout << Opt << std::endl;
	Opt = a;
	std::cout << Opt << std::endl;
	Opt = "defdef";
	std::cout << Opt << std::endl;

	std::string b = Opt;
	std::cout << b << std::endl;
}


void VectorTypeTest()
{
	std::vector<int> tmpvec(10, 3);
	COptionElem Opt(tmpvec);
	std::cout << Opt << std::endl;
	Opt = tmpvec;
	std::cout << Opt << std::endl;

	std::vector<int> b = Opt;
	std::cout << b.size() << std::endl;
}


void MapTypeTest()
{
	std::map<std::string, int> tmpmap ={ {"abc", 1}, {"def", 2} };
	COptionElem Opt(tmpmap);
	std::cout << Opt << std::endl;
	
	Opt = tmpmap;
	std::cout << Opt << std::endl;

}




}