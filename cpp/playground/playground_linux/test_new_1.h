// new测试1
#pragma once
#include <iostream>
#include "test_new.h"

using namespace std;

namespace test_new
{
	void test1()
	{
		cout << "test1()开始" << endl;

		A* a = new A;

		delete a;

		cout << "test1()结束" << endl;
	}

	void test2()
	{
		cout << "test2()开始" << endl;

		int* a = new int[10];

		for (int i = 0; i < 10; i++)
			a[i] = 10;

		delete[] a;

		cout << "test2()结束" << endl;
	}
}
