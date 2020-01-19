// new测试
// 这里没有搞明白,需要理论基础知识,仅仅是测试不知道原理和输出结果的原因
#pragma once
#include <iostream>

using namespace std;

namespace test_new
{

	class A
	{
	public:
		A() { cout << "A(),this:" << this << endl; }
		~A() { cout << "~A(),this:" << this << endl; }
	public:
		int a;
	};

	void test();
}
