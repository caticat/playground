// 引用测试
#pragma once
#include <iostream>

using namespace std;

namespace test_reference
{
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
		~A()
		{
			cout << "~A()" << endl;
		}
		const Pos& GetPos() { return p; }
	private:
		Pos p;
	};

	void test();
	void test_change();
}
