#include "test_try_catch.h"
#include <iostream>

namespace test_try_catch
{
	using namespace std;

	void test()
	{
		try
		{
			cout << 1 << endl;
		}
		catch (...)
		{
			cout << 2 << endl;
		}
		
		cout << 3 << endl;
	}
}
