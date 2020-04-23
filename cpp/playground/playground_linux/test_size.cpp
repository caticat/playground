#include "test_size.h"
#include <iostream>
#include <time.h>

namespace test_size
{
	using namespace std;

	void test()
	{
		cout << "clock_t size:" << sizeof(clock_t) << endl;
		cout << "int size:" << sizeof(int) << endl;
		cout << "uint32_t size:" << sizeof(uint32_t) << endl;
		cout << "uint64_t size:" << sizeof(uint64_t) << endl;
	}
}
