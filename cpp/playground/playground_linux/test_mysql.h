#pragma once

#include <iostream>
#include <sstream>
#include <hiredis/hiredis.h>

using namespace std;

namespace test_mysql
{
	void test();
	void test_stress();
	void test_stress_thread();
}
