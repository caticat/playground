#include "test_callgrind.h"
#include <iostream>

namespace test_callgrind
{
	// valgrind --log-file=./valgrind_report.log --leak-check=full --show-leak-kinds=all --show-reachable=yes ./playground_linux.out
	void test1()
	{
		cout << "test1()" << endl;
	}

	void test()
	{
		cout << "开始" << endl;

		test1();

		cout << "结束" << endl;
	}
}
