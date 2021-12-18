#pragma once
#include "OptionElementTestCases.h"
#include "TestUtils.h"

namespace OptElemTest
{

void TestSuite()
{
	REGISTERTESTCASE(UndefinedTypeTest)
	REGISTERTESTCASE(IntTypeTest)
	REGISTERTESTCASE(UIntTypeTest)
	REGISTERTESTCASE(CharTypeTest)
	REGISTERTESTCASE(UCharTypeTest)
	REGISTERTESTCASE(BoolTypeTest)
	REGISTERTESTCASE(StringTypeTest)
	REGISTERTESTCASE(VectorTypeTest)
	REGISTERTESTCASE(MapTypeTest)
}

	

}
