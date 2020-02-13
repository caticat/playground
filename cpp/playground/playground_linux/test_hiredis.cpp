#include "test_hiredis.h"
#include "test_time_cost.h"
#include <thread>

namespace test_hiredis
{
	static const string k_REDIS_HOST = "127.0.0.1";
	static const int k_REDIS_PORT = 63791;

	void test()
	{
		//test_basic();
		//test_common();
		//test_binary();
		//test_user();
		//test_stress();
		test_stress_thread();
		//test_stress_simple();
	}

	void test_basic()
	{
		CRedis r;
		if (!r.connect(k_REDIS_HOST, k_REDIS_PORT))
		{
			cout << "connect redis failed." << endl;
			return;
		}

		// 普通字符串
		r.setString("abc", "abc123");
		string ret = r.getString("abc");
		cout << "1get:" << ret << endl;
		ret = r.getString("abcd");
		cout << "2get:" << ret << endl;

		//普通数字
		r.setInt("abc", 9323372036854775807);
		uint64_t iret = r.getInt("abc");
		cout << "1get:" << iret << "," << (int64_t)iret << endl;
		iret = r.getInt("abcd");
		cout << "2get:" << iret << endl;

		//哈希字符串
		r.hsetString("t", "abc", "tabc123");
		ret = r.hgetString("t", "abc");
		cout << "1hget:" << ret << endl;
		ret = r.hgetString("t", "abcd");
		cout << "2hget:" << ret << endl;

		//哈希数字
		r.hsetInt("t", "abc", 9333372036854775807);
		iret = r.hgetInt("t", "abc");
		cout << "1hget:" << iret << "," << (int64_t)iret << endl;
		iret = r.hgetInt("t", "abcd");
		cout << "2hget:" << iret << endl;

	}

	void test_common()
	{
		CRedis r;
		if (!r.connect(k_REDIS_HOST, k_REDIS_PORT))
		{
			cout << "connect redis failed." << endl;
			return;
		}

		// 通用接口测试
		//ret = r.hgetStringFmt("hget %s %s", "t", "abc");
		//cout << "结果:" << ret << "," << r.hgetString("t", "abc") << endl;
		//redisReply* a = r.cmd("get %s", "abc");
		////redisReply* a = r.cmd("get abc");
		//cout << "cmd:" << a->str << endl;
		//freeReplyObject(a);
	}
	void test_binary()
	{
		CRedis r;
		if (!r.connect(k_REDIS_HOST, k_REDIS_PORT))
		{
			cout << "connect redis failed." << endl;
			return;
		}

		char a[10];
		for (int i = 0; i < 10; i++)
		{
			a[i] = char(97 + i);
		}
		a[4] = '\0';
		string b(a, 10);
		const char* c = b.c_str();
		for (int i = 0; i < b.length(); i++)
		{
			cout << "测试前:" << i << ",值:" << c[i] << endl;
		}
		r.hsetString("t1", "btest", b);
		string d = r.hgetString("t1", "btest");
		const char* e = d.c_str();
		for (int i = 0; i < d.length(); i++)
		{
			cout << "测试后:" << i << ",值:" << e[i] << endl;
		}
	}

	void test_user()
	{
		CRedis r;
		if (!r.connect(k_REDIS_HOST, k_REDIS_PORT))
		{
			cout << "connect redis failed." << endl;
			return;
		}

		r.hsetString("user:1001", "base", "abc123");
		r.hsetString("user:1002", "base", "abc1234");
		r.hsetString("user:1003", "base", "abc12345");
		cout << "1:" << r.hgetString("user:1001", "base") << endl;
		cout << "2:" << r.hgetString("user:1002", "base") << endl;
		cout << "3:" << r.hgetString("user:1003", "base") << endl;
	}

	void test_stress()
	{
		CRedis r;
		if (!r.connect(k_REDIS_HOST, k_REDIS_PORT))
		{
			cout << "connect redis failed." << endl;
			return;
		}

		// 生成测试用数据
		//int size = 1000;
		//int dataLen = 1024 * 1024;
		int size = 10000;
		int dataLen = 1024 * 64;
		//int size = 100000;
		//int dataLen = 256;
		stringstream ss;
		string data[size];
		test_time_cost::CTimeCostSimple cost;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < dataLen; j++)
			{
				ss << char('a' + (rand() % ('z' - 'a' + 1)));
			}
			data[i] = ss.str();
			ss.str("");
			//cout << "初始化数据:" << i << ",内容:" << data[i] << endl;
		}
		cout << "初始化数据完成" << endl;
		cost.Check();

		// 写入测试用数据
		for (int i = 0; i < size; i++)
		{
			ss << "stest:" << i;
			r.setString(ss.str(), data[i]);
			ss.str("");
		}
		cout << "写数据库完成" << endl; // 每秒写:259,612,775.4394652字节
		cost.Check();

		// 读取数据
		string res;
		for (int i = 0; i < size; i++)
		{
			ss << "stest:" << i;
			res = r.getString(ss.str());
			//cout << "读取数据:" << i << ",内容:" << res << endl;
			ss.str("");
		}
		cout << "读数据库完成" << endl; // 每秒读:637,545,000.3617661字节
	}

	void test_stress_thread_set(int dataPerThread, const string& data, CRedis* pr)
	{
		CRedis& r = *pr;

		// 写入测试用数据
		for (int i = 0; i < dataPerThread; i++)
		{
			r.setString("tss", data);
		}
		//cout << "写数据库完成" << endl;
	}

	void test_stress_thread_get(int dataPerThread, CRedis* pr)
	{
		CRedis& r = *pr;

		// 写入测试用数据
		for (int i = 0; i < dataPerThread; i++)
		{
			r.getString("tss");
		}
		//cout << "读数据库完成" << endl;
	}

	void test_stress_thread()
	{
		int threadNum = 50;
		int size = 100000;
		int dataLen = 1024 * 64;

		int dataPerThread = size / threadNum;

		// 生成测试用数据
		stringstream ss;
		for (int j = 0; j < dataLen; j++)
		{
			ss << char('a' + (rand() % ('z' - 'a' + 1)));
		}
		string data = ss.str();

		// 生成链接
		CRedis r[threadNum];
		for (int i = 0; i < threadNum; i++)
		{
			if (!r[i].connect(k_REDIS_HOST, k_REDIS_PORT))
			{
				cout << "connect redis failed." << endl;
				return;
			}
		}

		test_time_cost::CTimeCostSimple cost;
		thread* arrThread[threadNum];
		for (int i = 0; i < threadNum; i++)
		{
			arrThread[i] = new thread(test_stress_thread_set, dataPerThread, data, &r[i]);
		}

		for (int i = 0; i < threadNum; i++)
		{
			arrThread[i]->join();
		}
		cout << "写处理完成" << endl;
		cost.Check();

		for (int i = 0; i < threadNum; i++)
		{
			delete arrThread[i];
		}
		cost.Reset();

		for (int i = 0; i < threadNum; i++)
		{
			arrThread[i] = new thread(test_stress_thread_get, dataPerThread, &r[i]);
		}

		for (int i = 0; i < threadNum; i++)
		{
			arrThread[i]->join();
		}
		cout << "读处理完成" << endl;
		cost.Check();

		for (int i = 0; i < threadNum; i++)
		{
			delete arrThread[i];
		}
	}

	void test_stress_simple()
	{
		CRedis r;
		if (!r.connect(k_REDIS_HOST, k_REDIS_PORT))
		{
			cout << "connect redis failed." << endl;
			return;
		}

		// 生成测试用数据
		//int size = 1000;
		//int dataLen = 1024 * 1024;
		int size = 10000;
		int dataLen = 1024 * 64;
		//int size = 100000;
		//int dataLen = 256;
		stringstream ss;
		for (int j = 0; j < dataLen; j++)
		{
			ss << char('a' + (rand() % ('z' - 'a' + 1)));
		}
		string data = ss.str();

		// 写入测试用数据
		test_time_cost::CTimeCostSimple cost;
		for (int i = 0; i < size; i++)
		{
			r.setString("tss", data);
		}
		cout << "写数据库完成" << endl;
		cost.Check();

		// 读取数据
		string res;
		for (int i = 0; i < size; i++)
		{
			res = r.getString("tss");
			//cout << "读取数据:" << i << ",内容:" << res << endl;
		}
		cout << "读数据库完成" << endl; // 每秒读:637,545,000.3617661字节
	}
}