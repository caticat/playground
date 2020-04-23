#include "test_reference.h"
#include "test_reference_r.h"

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

	void test_base_1(A& a)
	{
		cout << "a:" << a.GetPos().x << endl;
		auto b = dynamic_cast<B*>(&a);
		cout << "b:" << b->m_b << endl;

		//int array_temp[100];
		//int a = array_temp[200];
	}
	void test_base()
	{
		B b;
		b.m_b = 10;
		test_base_1(b);
	}

	void test_classC()
	{
		C c;
		c.m_data = 10;
		test_classCr(c);
		
		vector<C> v;
		v.push_back(c);
		c.m_data = 20;
		v.push_back(c);
		test_classCrv(v);
	}

	void test_classCr(C& c)
	{
		cout << c.m_data << endl;
	}

	void test_classCrv(vector<C>& v)
	{
		for (vector<C>::iterator itr = v.begin(); itr != v.end(); ++itr)
		{
			cout << "itr:" << itr->m_data << endl;
		}
	}
}