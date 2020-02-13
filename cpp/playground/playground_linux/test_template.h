// 模板测试
#pragma once
#include <iostream>

using namespace std;

namespace test_template
{
	template <typename T>
	class TA
	{
	public:
		T* newT()
		{
			return (T*)(::operator new (sizeof(T)));
		}
	};

	template <typename T>
	class TB
	{
	public:
		T* newT()
		{
			return new (m_ta.newT())T;
		}

		TA<T> m_ta;
	};

	class C
	{
	public:
		C()
		{
			cout << "C()" << endl;
		}

		~C()
		{
			cout << "~C()" << endl;
		}

		void test()
		{
			cout << "C::test()" << endl;
		}
	};

	void test();
}
