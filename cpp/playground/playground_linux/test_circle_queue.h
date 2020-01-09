/*
	循环队列
*/

#pragma once
#include <iostream>

using namespace std;

namespace test_circle_queue
{
	struct CircleQueue
	{
		CircleQueue(int s)
		{
			data = new int[s];
			front = 0;
			back = 0;
			size = s;
			inSaveLoop = true;

			cout << "构造" << endl;
		}

		~CircleQueue()
		{
			if (data != nullptr)
			{
				delete[] data;
				data = nullptr;
			}
			cout << "析构" << endl;
		}

		bool Push(int i)
		{
			int f = getFreeCount();
			if (f == 0)
			{
				cout << "添加失败" << endl;
				return false;
			}

			data[back] = i;
			back++;
			if (back >= size)
			{
				back = 0;
				inSaveLoop = false;
				cout << "添加游标循环" << endl;
			}
			cout << "添加成功" << endl;
			return true;
		}

		int Pop()
		{
			if (isEmpty())
			{
				cout << "获取没有数据了" << endl;
				return 0;
			}
			int ret = data[front];
			front++;
			if (front >= size)
			{
				front = 0;
				inSaveLoop = true;
				cout << "获取游标循环了" << endl;
			}
			cout << "获取成功" << endl;
			return ret;
		}

		int getFreeCount()
		{
			if (back == front)
			{
				if (inSaveLoop)
				{
					return size;
				}
				else
				{
					return 0;
				}
			}
			return (back > front) ? (size - back + front) : (front - back);
		}

		bool isEmpty()
		{
			return (back == front) ? (inSaveLoop) : (false);
		}

		int* data;
		int front;
		int back;
		int size;
		bool inSaveLoop;
	};

	void test();
}
