#include "test_reference.h"

namespace test_reference
{
	void test()
	{
		A a;
		Pos b = a.GetPos();
		b.x = 10;

		const Pos& c = a.GetPos();
		cout << c.x << endl;
	}

	void test_change_1(Pos& a)
	{
		cout << "change1,x:" << a.x << endl;
		Pos b;
		b.x = 11;
		b.y = 12;
		a = b;
	}
	void test_change()
	{
		Pos a;
		a.x = 1;
		a.y = 2;
		cout << "函数调用前:" << a.x << endl;
		test_change_1(a);
		cout << "函数调用后:" << a.x << endl;
	}
}