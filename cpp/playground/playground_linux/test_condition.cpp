// 条件测试

#pragma once

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
