#include "test_perf.h"

namespace test_perf
{
	void test1()
	{
		int j = 0;
		for (int i = 0; i < 10000; i++)
			j += 2;
	}

	void test2()
	{

	}
	void test3()
	{
		int i = 0;
		while (i)
			i++;
	}
}
