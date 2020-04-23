#include "test_stack_protector.h"
#include <iostream>

namespace test_stack_protector
{
	using namespace std;

	void test2(int* a)
	{
		*(a - 2) = 10;
		//for (int i = 0; i < )
	}

	void test1()
	{
		int a[3];
		test2(a);
	}

	void test()
	{
		cout << "begin" << endl;
		test1();
		cout << "end" << endl;
	}
}
