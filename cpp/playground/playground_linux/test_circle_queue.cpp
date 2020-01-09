#include "test_circle_queue.h"

namespace test_circle_queue
{

	void test()
	{
		cout << 111 << endl;

		CircleQueue cq(2);
		cout << "empty:" << cq.isEmpty() << endl;
		cout << "free:" << cq.getFreeCount() << endl;
		cq.Push(1);
		cout << "empty:" << cq.isEmpty() << endl;
		cout << "free:" << cq.getFreeCount() << endl;
		cout << "pop:" << cq.Pop() << endl;
		cout << "empty:" << cq.isEmpty() << endl;
		cout << "free:" << cq.getFreeCount() << endl;
		cq.Push(1);
		cq.Push(2);
		cout << "empty:" << cq.isEmpty() << endl;
		cout << "free:" << cq.getFreeCount() << endl;
		cq.Push(3);
		cout << "pop:" << cq.Pop() << endl;
		cout << "pop:" << cq.Pop() << endl;
		cout << "pop:" << cq.Pop() << endl;
		cout << "empty:" << cq.isEmpty() << endl;
		cout << "free:" << cq.getFreeCount() << endl;

		cout << 222 << endl;
	}
}
