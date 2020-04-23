// 引用测试
#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace test_reference
{
	class C;

	struct Pos
	{
	public:
		Pos() : x(0), y(0)
		{
			cout << "Pos()" << endl;
		}
		~Pos()
		{
			cout << "~Pos()" << x << endl;
		}
		Pos(const Pos& p)
		{
			x = p.x;
			y = p.y;
			cout << "Pos(Pos)" << endl;
		}
	public:
		int x;
		int y;
	};

	class A
	{
	public:
		A()
		{
			cout << "A()" << endl;
		}
		virtual ~A()
		{
			cout << "~A()" << endl;
		}
		const Pos& GetPos() { return p; }
	private:
		Pos p;
	};

	class B : public A
	{
	public:
		int m_b = 0;
	};

	void test();
	void test_change();
	void test_base();
	void test_classC();
	void test_classCr(C& c);
	void test_classCrv(vector<C>& v);
}
