// slt::array测试
/*
	array对于数组越界并没有什么特殊处理
*/

#include "test_array.h"
#include <iostream>
#include <array>

using namespace std;

namespace test_array
{
	void test1()
	{
		array<int, 10> a{ 1,2,3,4,5,6 };
		for (int i = 0; i < int(a.size()); ++i)
		{
			cout << a[i] << endl;
		}

		a[20] = 100;
		cout << a[20] << endl;
		cout << a.size() << "/" << a.max_size() << endl;

		cout << a.at(2) << endl;
		cout << a.at(20) << endl;
	}

	void test3(int a[10])
	{
		cout << "test3:a:" << sizeof(a) << endl;
	}

	void test4(int* a)
	{
		cout << "test4:a:" << sizeof(a) << endl;
	}

	void test5(A* a)
	{
		cout << "a.m_data:" << sizeof(a->m_data) << endl;
	}

	int g_data[20];
	void test2()
	{
		A a;
		cout << "ptr:" << sizeof(&a) << endl;
		cout << "a.m_data:" << sizeof(a.m_data) << endl;
		cout << "g_data:" << sizeof(g_data) << endl;

		int b[10];
		test3(b);
		test3(g_data);
		test4(b);
		test5(&a);
	}

	void test3()
	{
		int a = 1;
		int b = 2;
		int c = min(a, b);
		int d = max(a, b);
		cout << c << endl;
		cout << d << endl;
	}

	void test()
	{
		//test1();
		//test2();
		test3();
	}
}
