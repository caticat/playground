#include <iostream>

#include "test_condition.h"
#include "test_circle_queue.h"
#include "test_perf.h"

using namespace std;

int main()
{
	cout << "playground开始" << endl;

	//test_condition::test(); // condition
	test_circle_queue::test(); // 循环队列
	//test_perf::test1(); // perf测试
	//test_perf::test2(); // perf测试

	cout << "playground结束" << endl;

	return 0;
}
