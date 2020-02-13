#include "test_set.h"
#include <set>
#include <iostream>

namespace test_set
{
	using namespace std;

	void A::test()
	{
		cout << "A::test()" << endl;
	}

	void test()
	{
		set<A*> a;
		set<A*>::iterator it = a.begin();
		A* b = *it;
		if (b)
		{
			cout << "不为空" << endl;
			b->test();
		}
		else
		{
			cout << "为空" << endl;
		}
	}
}
