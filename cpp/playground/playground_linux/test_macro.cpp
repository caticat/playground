#include "test_macro.h"

namespace test_macro
{
	void test()
	{
		CALC_TIME_COST(abc, "123", 10);
		//CALC_TIME_COST_DEFAULT(AAA, "456");
		for (int i = 0; i < 1000000; ++i)
		{

		}
		//printf("%d", abc);
		printf("123abc\n");
	}
}
