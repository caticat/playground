// 堆栈保护测试
// g++增加编译选项:-fstack-protector-all
// 再vs中直接增加其他选项无效，自己使用g++编译可以，但是一样看不到堆栈

#pragma once

namespace test_stack_protector
{
	void test();
}
