#include "test_pointer.h"
#include <iostream>

namespace test_pointer
{
	using namespace std;

	void test1(A** a)
	{
		*a = new A;
		(*a)->m_a = 100;
	}

	void test2(A*& a)
	{
		a = new A;
		(*a).m_a = 200;
	}

	void test()
	{
		cout << "begin" << endl;
		A* a = nullptr;
		test1(&a);
		cout << "1a:" << a << endl;
		if (a)
		{
			cout << "1data:" << a->m_a << endl;
			delete a;
			a = nullptr;
		}

		test2(a);
		cout << "2a:" << a << endl;
		if (a)
		{
			cout << "2data:" << a->m_a << endl;
			delete a;
			a = nullptr;
		}

		cout << "end" << endl;
	}
}
