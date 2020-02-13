#include "test_argv.h"
#include <stdarg.h>

namespace test_argv
{
	void t(const char* fmt, ...)
	{
		char a[20];
		va_list valist;
		va_start(valist, fmt);
		vsnprintf(a, 20, fmt, valist);
		va_end(valist);
		cout << a << endl;
	}

	void test()
	{
		cout << 111 << endl;

		t("abc%s,%d", "ddd", 2);
	}
}