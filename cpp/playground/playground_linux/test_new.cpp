#include "test_new.h"
#include "test_new_1.h"

void* operator new(size_t size)
{
	cout << "new(),size:" << size << endl;
	if (size == 0)
		return nullptr;
	void* p = malloc(size);
	return p;
}

void* operator new[](size_t size)
{
	cout << "new[](), size:" << size << endl;
	return operator new(size);
}

void operator delete(void* p)
{
	cout << "delete()" << endl;
	if (p != nullptr)
		free(p);
}

void operator delete[](void* p)
{
	cout << "delete[]()" << endl;
	operator delete(p);
}

namespace test_new
{
	void test3()
	{
		cout << "test3()开始" << endl;

		A** a = new A*[10];

		delete[] a;

		cout << "test3()结束" << endl;
	}

	void test()
	{
		cout << "test()开始" << endl;

		A* a = new A;
		a->a = 256;
		delete a;

		test1();
		test2();
		test3();

		cout << "test()结束" << endl;
	}
}