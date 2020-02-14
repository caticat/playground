#pragma once

#include <iostream>

namespace test_static
{
	using namespace std;

	class A
	{
	public:
		void test()
		{
			static int i = 0;
			i++;
			cout << "i:" << i << endl;
		}
	};

	void test();
}
