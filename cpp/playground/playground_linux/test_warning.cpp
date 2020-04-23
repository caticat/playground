#include "test_warning.h"
#include <iostream>

namespace test_warning
{
	using namespace std;

#define MARK_USED(A) if (A) {}

	void test()
	{
		cout << "begin" << endl;

		int a;
		MARK_USED(a);
		//string b;
		//MARK_USED(b);
		bool c;
		MARK_USED(c);
		char d;
		MARK_USED(d);
		cout << 1 << endl;

		cout << "end" << endl;
	}
}
