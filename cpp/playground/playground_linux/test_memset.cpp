#include "test_memset.h"
#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <cstring>

namespace test_memset
{
	using namespace std;

	void test_memset()
	{
		int l = 10;
		char a[l];

		memset(a, 0, l);
		for (int i = 0; i < l; i++)
		{
			cout << a[i] << endl;
		}

		// 这个函数没有找到
		//memset_s(a, l, 0, 20);
		//for (int i = 0; i < l; i++)
		//{
		//	cout << a[i] << endl;
		//}
	}

	void test_strcpy()
	{
		char a[] = "123456";
		char b[3];
		//char b[7];
		//strcpy(b, a);

		cout << a << endl;
		cout << b << "," << sizeof(b) << "," << strlen(b) << endl;

		strncpy(b, a, 3); // 不会在结尾追加'\0'
		cout << b << "," << sizeof(b) << "," << strlen(b) << endl;
	}

	void test_strncpy()
	{
		// strncpy不会给字符串结尾追加'\0'结束
		char a[] = "123456";
		char b[] = "987654321";
		cout << "a:" << a << ",b:" << b << endl;
		cout << "la:" << strlen(a) << ",sa:" << sizeof(a) << ",lb:" << strlen(b) << ",sb:" << sizeof(b) << endl;
		strncpy(b, a, strlen(a));
		cout << "b:" << b << ",lb:" << strlen(b) << ",sb:" << sizeof(b) << endl;

		// strncpy会超出dest的长度
		//char a[] = "123456";
		//char b[] = "321";
		//memset(b + 3, '1', 10);
		//cout << "a:" << a << ",b:" << b << endl;
		//cout << "la:" << strlen(a) << ",sa:" << sizeof(a) << ",lb:" << strlen(b) << ",sb:" << sizeof(b) << endl;
		//strncpy(b, a, strlen(a));
		//cout << "b:" << b << ",lb:" << strlen(b) << ",sb:" << sizeof(b) << endl;

		// strncpy会超出dest的长度
		//char a[] = "123456";
		//memset(a + 6, '1', 10);
		//char b[] = "987654321";
		//cout << "a:" << a << ",b:" << b << endl;
		//cout << "la:" << strlen(a) << ",sa:" << sizeof(a) << ",lb:" << strlen(b) << ",sb:" << sizeof(b) << endl;
		//strncpy(b, a, strlen(b));
		////memcpy(b, a, strlen(b));
		//cout << "b:" << b << ",lb:" << strlen(b) << ",sb:" << sizeof(b) << endl;
	}

	void test_memcpy()
	{
		char a[] = "123";
		char b[] = "999999";
		char c[] = "888888";
		char d[] = "777777";
		char e[] = "666666";
		memcpy(b, a, sizeof(b));
		strncpy(c, a, sizeof(c));
		memcpy(d, a, sizeof(a));
		strncpy(e, a, sizeof(a));

		cout << sizeof(a) << "," << strlen(a) << endl;
		cout << b << "," << sizeof(b) << "," << strlen(b) << endl;
		cout << c << "," << sizeof(c) << "," << strlen(c) << endl;
		cout << d << "," << sizeof(d) << "," << strlen(d) << endl;
		cout << e << "," << sizeof(e) << "," << strlen(e) << endl;

		char h[] = "999999";
		char i[] = "888888";
		char j[] = "777777";
		char k[] = "666666";
		memcpy(h, a, strlen(h));
		strncpy(i, a, strlen(i));
		memcpy(j, a, strlen(a));
		strncpy(k, a, strlen(a));
		cout << h << "," << sizeof(h) << "," << strlen(h) << endl;
		cout << i << "," << sizeof(i) << "," << strlen(i) << endl;
		cout << j << "," << sizeof(j) << "," << strlen(j) << endl;
		cout << k << "," << sizeof(k) << "," << strlen(k) << endl;
	}

#define MEMCPY(dest, destLen, src, srcLen) \
	do \
	{ \
		size_t cpyLen = size_t(srcLen); \
		if ((destLen) < (srcLen)) \
		{ \
			cout << "[ERROR]memcpy destLen:" << (destLen) << ",srcLen:" << (srcLen) << endl; \
			cpyLen = size_t(destLen); \
		} \
		memcpy((dest), (src), cpyLen); \
	} while(0)

	void test_memcpy2()
	{
		char a[] = "0123456";
		char b[] = "222";
		memset(b + 3, 'a', 3);
		MEMCPY(b, sizeof(b), a, sizeof(a));
		cout << "size:" << sizeof(b) << ",len:" << strlen(b) << ",data:" << b << endl;
	}

	void test_snprintf()
	{
		char a[5] = { 0 };
		char b[] = "123456789";
		snprintf(a, sizeof(a), "%s", b);
		cout << "la:" << strlen(a) << ",sa:" << sizeof(a) << endl;
		cout << "a:" << a << endl;
	}

	void test()
	{
		cout << "begin" << endl;

		//test_memset();
		//test_strcpy();
		//test_memcpy();
		test_memcpy2();
		//test_strncpy();
		//test_snprintf();

		cout << "end" << endl;
	}
}
