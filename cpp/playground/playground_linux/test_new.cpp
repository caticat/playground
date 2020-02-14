#include "test_new.h"
#include "test_new_1.h"

//void* operator new(size_t size)
//{
//	cout << "new(),size:" << size << endl;
//	if (size == 0)
//		return nullptr;
//	void* p = malloc(size);
//	return p;
//}
//
//void* operator new[](size_t size)
//{
//	cout << "new[](), size:" << size << endl;
//	return operator new(size);
//}
//
//void operator delete(void* p)
//{
//	cout << "delete()" << endl;
//	if (p != nullptr)
//		free(p);
//}
//
//void operator delete[](void* p)
//{
//	cout << "delete[]()" << endl;
//	operator delete(p);
//}

namespace test_new
{
	void test3()
	{
		cout << "test3()开始" << endl;

		A** a = new A*[10];

		delete[] a;

		cout << "test3()结束" << endl;
	}

	void test4()
	{
		cout << "test4()开始" << endl;

		int count = 3;
		A* a = (A*)operator new(sizeof(A) * count);
		for (int i = 0; i < count; i++)
		{
			new(&a[i])A();
		}

		delete[] a;

		cout << "test4()结束" << endl;
	}

	void test()
	{
		cout << "test()开始" << endl;

		//A* a = new A;
		//a->a = 256;
		//delete a;

		//test1();
		//test2();
		//test3();

		test4();

		cout << "test()结束" << endl;
	}
}