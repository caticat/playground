#include <iostream>
#include <string>

#include "test_condition.h"
#include "test_circle_queue.h"
#include "test_perf.h"
#include "test_time_cost.h"
#include "test_reference.h"
#include "test_macro.h"
#include "test_typedef.h"
#include "test_new.h"

using namespace std;

int main()
{
	cout << "playground开始" << endl;

	//test_condition::test(); // condition
	//test_circle_queue::test(); // 循环队列
	//test_perf::test1(); // perf测试
	//test_perf::test2(); // perf测试
	//test_time_cost::testSimple(); // 时间消耗计算测试,1
	//test_time_cost::test(); // 时间消耗计算测试,2
	//test_reference::test(); // 引用测试
	//test_reference::test_change(); // 引用测试,函数调用与内容修改
	//test_macro::test(); // 测试宏
	//test_typedef::test(); // typedef作用域测试
	test_new::test(); // new测试

	cout << "playground结束" << endl;

	return 0;
}
