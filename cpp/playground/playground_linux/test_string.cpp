#include "test_string.h"
#include <iostream>

namespace test_string
{
	using namespace std;

	void test1()
	{
		string a = "aaa";
		a += ';';
		//int i = 10;
		//a += i + ';';
		cout << a << endl;

		int i = 10;
		float j = 1.5;
		i = int(float(i) * j);
		cout << i << endl;
	}

	void test2()
	{
		std::string s1("hello");
		std::cout << "s1=" << s1 << " s1.size=" << s1.size() << " s1.capacity=" << s1.capacity() << endl;

		std::cout << "after resize to 2" << endl;
		s1.resize(2); //尺寸由5改变为2，多余字符被截掉了,只剩下he
		std::cout << "s1=" << s1 << " s1.size=" << s1.size() << " s1.capacity=" << s1.capacity() << endl;

		std::cout << "after resize to 100" << endl;
		s1.resize(100);//尺寸由2改变为100,后面的数据被填充了98个a
		std::cout << "s1=" << s1 << " s1.size=" << s1.size() << " s1.capacity=" << s1.capacity() << endl;

		std::cout << "\n";
		std::cout << "===================================================================" << endl;
		std::cout << "\n";

		std::string s2("hello");
		std::cout << "s2=" << s2 << " s2.size=" << s2.size() << " s2.capacity=" << s2.capacity() << endl;

		std::cout << "after reserve to 20" << endl;
		s2.reserve(20);  //只改变capacity()的大小，其他的不变
		std::cout << "s2=" << s2 << " s2.size=" << s2.size() << " s2.capacity=" << s2.capacity() << endl;

		std::cout << "after reserve to 2" << endl;
		s2.reserve(2);   //只改变capacity()的大小，其他的不变
		std::cout << "s2=" << s2 << " s2.size=" << s2.size() << " s2.capacity=" << s2.capacity() << endl;
	}

	void test3()
	{
		string a = "abc";
		cout << "s:" << a << ",l:" << a.length() << ",c:" << a.capacity() << endl;
		//a.reserve(20);
		a += 'd';
		cout << "s:" << a << ",l:" << a.length() << ",c:" << a.capacity() << endl;
		a += "ef";
		cout << "s:" << a << ",l:" << a.length() << ",c:" << a.capacity() << endl;
	}

	void test()
	{
		//test1();
		//test2();
		test3();
	}
}
