// 堆测试
/*
	大顶堆,对应操作less(默认),数组的第一个元素为最大值(其他元素不一定)
	小顶堆,对应操作greater,数组的第一个元素为最小值(其他元素不一定)
	make_heap类似与排序,但是只排序第一个元素,取极值(这里的说明很不严谨,具体还是要参考堆的定义和实现)
	push_heap是再新增元素后处理
	heap_pop会使第一个元素变成最后一个元素,方便pop_back()
*/

#include "test_heap.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace test_heap
{
	void printVec(const vector<int>& vec)
	{
		for (auto itr = vec.begin(); itr != vec.end(); ++itr)
		{
			cout << *itr << " : ";
		}
		cout << ";" << endl;
	}

	void test()
	{
		int arr[] = { 8, 3, 4, 8, 9, 2, 3, 4, 10 };
		vector<int> vec(arr, arr + 9);
		cout << "make_heap之前:";
		printVec(vec);

		cout << "默认(less)make_heap:";
		make_heap(vec.begin(), vec.end());
		printVec(vec);

		cout << "(less)make_heap:";
		make_heap(vec.begin(), vec.end(), less<int>());
		printVec(vec);

		cout << "(greater)make_heap:";
		make_heap(vec.begin(), vec.end(), greater<int>());
		printVec(vec);

		cout << "此时,vec为小顶堆greater" << endl;
		cout << "push_back(3)" << endl;
		vec.push_back(3);
		cout << "默认(less)push_heap 此时push_heap失败";
		push_heap(vec.begin(), vec.end());
		printVec(vec);

		cout << "push_heap为greater和make_heap一致,此时push_heap成功:";
		push_heap(vec.begin(), vec.end(), greater<int>());
		printVec(vec);

		cout << "(greater,不然会失败)pop_heap:";
		pop_heap(vec.begin(), vec.end(), greater<int>());
		printVec(vec);
		vec.pop_back();
		printVec(vec);
	}
}
