// 枚举测试

#include "test_enum.h"
#include <iostream>

using namespace std;

namespace test_enum
{
	enum EA
	{
		EA_1 = 1,
		EA_2 = 2,
	};

	void test()
	{
		EA a = EA(3);
		EA b = EA_2;
		cout << a << endl;
		cout << b << endl;
	}
}
