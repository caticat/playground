#include "test_mysql.h"
#include "test_time_cost.h"
#include "mysql/mysql.h"
#include <thread>

namespace test_mysql
{
	static const string k_HOST = "127.0.0.1";
	static const int k_PORT = 3306;
	static const string k_NAME = "root";
	static const string k_PASS = "root";
	static const string k_DATABASE = "test";

	void test()
	{
		//test_stress();
		test_stress_thread();
	}

	void test_stress()
	{
		cout << "开始压力测试" << endl;
		MYSQL* conn = mysql_init(nullptr);
		if (conn == nullptr)
		{
			cout << "[ERROR]conn == nullptr" << endl;
			return;
		}

		if (!mysql_real_connect(conn, k_HOST.c_str(), k_NAME.c_str(), k_PASS.c_str(), k_DATABASE.c_str(), k_PORT, NULL, 0))
		{
			cout << "[ERROR]connect failed." << endl;
			return;
		}

		mysql_set_character_set(conn, "utf8");
		char value = 1;
		mysql_options(conn, MYSQL_OPT_RECONNECT, &value);

		cout << "mysql连接成功" << endl;

		// 生成测试用数据
		int size = 10000;
		int dataLen = 1024 * 64;
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
		mysql_query(conn, "truncate test;");
		cout << "初始化数据完成" << endl;
		cost.Check();

		// 写入测试用数据
		int err = 0;
		for (int i = 0; i < size; i++)
		{
			ss << "insert into test values (" << i << ", '" << data[i] << "');";
			//cout << i << ",sql:" << ss.str() << endl;
			//string tmp = "echo \"";
			//tmp += ss.str();
			//tmp += "\" > tmp.log";
			//system(tmp.c_str());
			err = mysql_query(conn, ss.str().c_str());

			if (err != 0)
			{
				cout << "插入数据失败，err:" << err << ",sql:" << ss.str() << endl;
				return;
			}
			ss.str("");
		}
		cout << "写数据库完成" << endl;
		cost.Check();

		// 读取数据
		string res;
		for (int i = 0; i < size; i++)
		{
			ss << "select data from test where id = " << i << ";";
			err = mysql_query(conn, ss.str().c_str());
			MYSQL_RES* res = mysql_store_result(conn);
			//if (mysql_num_rows(res) > 0)
			//{
			//	MYSQL_ROW row;
			//	uint32_t dwFields = mysql_num_fields(res);
			//	while ((row = mysql_fetch_row(res)) != NULL)
			//	{
			//		unsigned long * len = mysql_fetch_lengths(res);
			//		for (uint32_t i = 0; i < dwFields; i++)
			//		{
			//			string strData(row[i], len[i]);
			//			cout << "读取数据:" << i << ",data:" << strData << endl;
			//		}
			//	}
			//}
			mysql_free_result(res);

			if (err != 0)
			{
				cout << "读取数据失败，err:" << err << ",sql:" << ss.str() << endl;
				return;
			}
			//else
			//{
			//	cout << "读取数据成功,sql:" << ss.str() << endl;
			//}
			ss.str("");
		}
		cout << "读数据库完成" << endl;
		cost.Check();

		mysql_close(conn);
	}

	void test_stress_thread_set(int id, int dataPerThread, const string& data, MYSQL* conn)
	{
		// 写入测试用数据
		int err = 0;
		stringstream ss;
		for (int i = 0; i < dataPerThread; i++)
		{
			ss << "insert into test values (" << (id * dataPerThread + i) << ", \"" << data << "\");";
			err = mysql_query(conn, ss.str().c_str());
			if (err != 0)
			{
				cout << "插入数据失败，err:" << err << ",sql:" << data << endl;
				return;
			}
			//else
			//{
			//	cout << "写入成功，sql：" << ss.str() << endl;
			//}
			ss.str("");
		}
		//cout << "写数据库完成" << endl;
	}

	void test_stress_thread_get(int dataPerThread, const string& data, MYSQL* conn)
	{
		// 读取测试用数据
		int err = 0;
		for (int i = 0; i < dataPerThread; i++)
		{
			err = mysql_query(conn, data.c_str());

			if (err != 0)
			{
				cout << "插入数据失败，err:" << err << ",sql:" << data << endl;
				return;
			}
			MYSQL_RES* res = mysql_store_result(conn);
			//if (mysql_num_rows(res) > 0)
			//{
			//	MYSQL_ROW row;
			//	uint32_t dwFields = mysql_num_fields(res);
			//	while ((row = mysql_fetch_row(res)) != NULL)
			//	{
			//		unsigned long * len = mysql_fetch_lengths(res);
			//		for (uint32_t i = 0; i < dwFields; i++)
			//		{
			//			string strData(row[i], len[i]);
			//			cout << "读取数据:" << i << ",data:" << strData << endl;
			//		}
			//	}
			//}
			mysql_free_result(res);
		}
		//cout << "读数据库完成" << endl;
	}

	void test_stress_thread()
	{
		int threadNum = 5;
		int size = 10;
		int dataLen = 64;

		int dataPerThread = size / threadNum;

		// 生成测试用数据
		string dataIn[threadNum];
		for (int i = 0; i < threadNum; i++)
		{
			stringstream ss;
			for (int j = 0; j < dataLen; j++)
			{
				ss << char('a' + (rand() % ('z' - 'a' + 1)));
			}
			dataIn[i] = ss.str();
		}
		string dataOut[threadNum];
		for (int i = 0; i < threadNum; i++)
		{
			stringstream ss;
			ss << "select data from test where id = " << (i * dataPerThread) << ";";
			dataOut[i] = ss.str();
		}

		// 生成链接
		MYSQL* arrConn[threadNum];
		for (int i = 0; i < threadNum; i++)
		{
			MYSQL* conn = mysql_init(nullptr);
			if (conn == nullptr)
			{
				cout << "[ERROR]conn == nullptr" << endl;
				return;
			}

			if (!mysql_real_connect(conn, k_HOST.c_str(), k_NAME.c_str(), k_PASS.c_str(), k_DATABASE.c_str(), k_PORT, NULL, 0))
			{
				cout << "[ERROR]connect failed." << endl;
				return;
			}

			mysql_set_character_set(conn, "utf8");
			char value = 1;
			mysql_options(conn, MYSQL_OPT_RECONNECT, &value);
			arrConn[i] = conn;
		}
		mysql_query(arrConn[0], "truncate test;");

		test_time_cost::CTimeCostSimple cost;
		thread* arrThread[threadNum];
		for (int i = 0; i < threadNum; i++)
		{
			arrThread[i] = new thread(test_stress_thread_set, i, dataPerThread, dataIn[i], arrConn[i]);
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
			arrThread[i] = new thread(test_stress_thread_get, dataPerThread, dataOut[i], arrConn[i]);
		}

		for (int i = 0; i < threadNum; i++)
		{
			arrThread[i]->join();
		}
		cout << "读处理完成" << endl;
		cost.Check();

		for (int i = 0; i < threadNum; i++)
		{
			mysql_close(arrConn[i]);
			delete arrThread[i];
		}
	}
}