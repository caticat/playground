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
#include "test_hiredis.h"
#include "test_mysql.h"
#include "test_argv.h"
#include "test_random.h"
#include "test_template.h"
#include "test_set.h"
#include "test_try_catch.h"
#include "test_static.h"
#include "test_epoll.h"
#include "test_size.h"
#include "test_sort.h"
#include "test_map.h"
#include "test_vtable.h"
#include "test_stack_protector.h"
#include "test_pointer.h"
#include "test_warning.h"
#include "test_string.h"
#include "test_valgrind.h"
#include "test_callgrind.h"
#include "test_unused_variable.h"
#include "test_enum.h"
#include "test_heap.h"
#include "test_array.h"
#include "test_memset.h"

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
	//test_reference::test_base(); // 引用测试
	//test_reference::test_classC(); // 引用测试头文件包含问题
	//test_macro::test(); // 测试宏
	//test_typedef::test(); // typedef作用域测试
	//test_new::test(); // new测试
	//test_hiredis::test(); // hiredis测试
	//test_mysql::test(); // mysql测试
	//test_argv::test(); // argv测试
	//test_random::test(); // random测试
	//test_template::test(); // 模板测试
	//test_set::test(); // set测试
	//test_try_catch::test(); // try_catch测试
	//test_static::test(); // static测试
	//test_epoll::test(); // epoll测试
	//test_size::test(); // size测试
	//test_sort::test(); // sort测试
	//test_map::test(); // map测试
	//test_vtable::test(); // vtable测试
	//test_stack_protector::test(); // stack_protector测试
	//test_pointer::test(); // test_pointer测试
	//test_warning::test(); // test_warning测试
	//test_string::test(); // test_string测试
	//test_valgrind::test(); // test_valgrind测试
	//test_callgrind::test(); // test_callgrind测试
	//test_unused_variable::test(); // test_unused_variable测试
	//test_enum::test(); // test_enum测试
	//test_heap::test(); // test_heap测试
	//test_array::test(); // test_array测试
	test_memset::test(); // test_memset测试

	cout << "playground结束" << endl;

	return 0;
}
