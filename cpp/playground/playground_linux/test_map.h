#pragma once
#include <iostream>
#include <map>

namespace test_map
{
	using namespace std;

	class A
	{
	public:
		A()
		{
			cout << "A()" << endl;
		}
		A(const A& a)
		{
			cout << "A(const A&)" << endl;
			this->a = a.a;
		}
		~A()
		{
			cout << "~A()" << endl;
		}

	public:
		int a = 0;
	};

	class B
	{
	public:
		map<int, int> m_map;
	};

	void test();
}
