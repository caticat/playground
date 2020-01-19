// typedef测试
#pragma once
#include <iostream>

using namespace std;

namespace test_typedef
{
	typedef int a_t;

	class A
	{
	public:
		typedef int b_t;
	public:
		b_t a;
	};

	void test();
}
