#include "test_unused_variable.h"
#include <iostream>

namespace test_unused_variable
{
	using namespace std;

#define MARK_USED(A) (void)(A)

	void test()
	{
		int a;
		MARK_USED(a);

		string b;
		MARK_USED(b);

		char c;
		MARK_USED(c);

		int d[10];
		MARK_USED(d);
		d[3] = 33;

		void* e;
		MARK_USED(e);

		int i = 3;
		for (; i < 5; i++)
			cout << i << endl;

		cout << d[3] << endl;

		enum EA
		{
			EA_1 = 0,
		};
		string f = "";
		//f += EA_1 + 10;
		f = 97;
		cout << ":" << f << ":" << endl;

		//int g = -1;
		//uint32_t h = uint32_t(g);
		//cout << "-->" << h << endl;

		//uint16_t h = 10;
		//uint16_t j = 0;
		//j += h;
		//cout << j << endl;
	}
}
