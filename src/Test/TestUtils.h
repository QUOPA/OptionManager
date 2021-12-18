#pragma once
#include <exception>
#include <iostream>
#include <string>

#define REGISTERTESTCASE(FN) std::cout << "< TEST CASE : " << #FN << " >" << std::endl; \
try { FN(); } \
catch (std::exception & e) { std::cout << "Exception : " << e.what() <<std::endl; } \
catch (...) { std::cout << "Exception : Unexpected" << std::endl; }


#define REGISTERTESTSUITE(NS) std::cout << "======== TEST SUITE : " << #NS << " ========" << std::endl; NS::TestSuite();



