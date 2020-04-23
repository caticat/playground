#pragma once
#include <set>

namespace test_valgrind
{
	using namespace std;

	void test();

	struct A
	{
	public:
		A();
		~A();
		set<int> m_a;
	};
}
