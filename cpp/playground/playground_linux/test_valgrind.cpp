#include "test_valgrind.h"
#include <iostream>
#include <vector>
#include <memory>

namespace test_valgrind
{
	// valgrind --log-file=./valgrind_report.log --leak-check=full --show-leak-kinds=all --show-reachable=yes ./playground_linux.out
	vector<A*> g_v;
	void test1()
	{
		cout << "内存测试开始" << endl;
		A* pA = new A;
		for (int i = 0; i < 3; i++)
		{
			pA->m_a.insert(3);
		}
		g_v.emplace_back(pA);
		cout << "内存测试结束" << endl;

		//for (vector<A*>::iterator it = g_v.begin(); it != g_v.end(); ++it)
		//{
		//	delete *it;
		//}
	}

	void test2()
	{
		//A* p = static_cast<A*>(::operator new (sizeof(A)));
		////::operator delete (p);
	}

	void test3()
	{
		shared_ptr<A> p(new A);
	}

	void test()
	{
		cout << "开始" << endl;

		//test1();
		//test2();
		test3();

		cout << "结束" << endl;
	}

	A::A()
	{
		cout << "构造A" << endl;
	}

	A::~A()
	{
		cout << "析构A" << endl;
	}
}
