// 条件测试
/*
	condition在pthread_cond_wait中会释放掉当前的锁,然后在pthread_cond_signal后会激活一个对应的锁
	使用pthread_cond_wait最好是使用while循环条件判断,因为可能有其他的线程还在竞争锁

	condition的使用总结
		1. 使用条件锁前必须先锁住对应的互斥锁。
		2. 件锁进入阻塞(pthread_cond_wait)时自动解开对应互斥锁，而一旦跳出阻塞立即再次取得互斥锁，而这两个操作都是原子操作。
*/

#pragma once

#include "test_condition.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

namespace test_condition
{
	int g_i = 0;

	pthread_mutex_t g_mutex;
	pthread_cond_t g_cond;

	void* consumer(void*)
	{
		cout << "consumer开始" << endl;
		for (int i = 0; i < 10; i++)
		{
			pthread_mutex_lock(&g_mutex);

			while (g_i == 0)
			{
				pthread_cond_wait(&g_cond, &g_mutex);
			}

			g_i--;
			cout << "consumer当前g_i:" << g_i << endl;

			pthread_mutex_unlock(&g_mutex);
		}

		return NULL;
	}

	void* producer(void*)
	{
		cout << "producer开始" << endl;
		for (int i = 0; i < 10; i++)
		{
			pthread_mutex_lock(&g_mutex);

			cout << "producer调用" << endl;
			g_i++;
			pthread_cond_signal(&g_cond);

			pthread_mutex_unlock(&g_mutex);

			sleep(1);
		}

		return NULL;
	}

	void test()
	{
		pthread_mutex_init(&g_mutex, NULL);
		pthread_cond_init(&g_cond, NULL);

		pthread_t pc;
		pthread_create(&pc, NULL, consumer, NULL);

		pthread_t pp;
		pthread_create(&pp, NULL, producer, NULL);

		pthread_join(pc, NULL);
		pthread_join(pp, NULL);

		pthread_mutex_destroy(&g_mutex);
		pthread_cond_destroy(&g_cond);
	}
}
