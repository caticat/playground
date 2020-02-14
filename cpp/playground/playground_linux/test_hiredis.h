//#pragma once
//
//#include <iostream>
//#include <sstream>
//#include <hiredis/hiredis.h>
//
//using namespace std;
//
//namespace test_hiredis
//{
//	void test();
//	void test_basic();
//	void test_common();
//	void test_user();
//	void test_binary();
//	void test_stress();
//	void test_stress_thread();
//	void test_stress_simple();
//
//	class CRedis
//	{
//	public:
//		CRedis()
//		{
//		}
//
//		~CRedis()
//		{
//			if (m_connect != nullptr)
//			{
//				redisFree(m_connect);
//				m_connect = nullptr;
//			}
//		}
//
//		bool connect(string host = "", int port = 0)
//		{
//			if (host != "")
//				m_host = host;
//			if (port != 0)
//				m_port = port;
//			if (m_connect != nullptr)
//			{
//				cout << "[ERROR]connect duplicated." << endl;
//				redisFree(m_connect);
//				m_connect = nullptr;
//			}
//
//			m_connect = redisConnect(m_host.c_str(), m_port);
//			if (m_connect == nullptr)
//			{
//				cout << "[ERROR]m_connect == nullptr" << endl;
//				return false;
//			}
//			if (m_connect->err)
//			{
//				cout << "[ERROR]connect error:" << m_connect->err << endl;
//				redisFree(m_connect);
//				m_connect = nullptr;
//				return false;
//			}
//
//			return true;
//		}
//
//		string getString(string key)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "get %s", key.c_str());
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]getString checkReply failed." << endl;
//				return "";
//			}
//			if (reply->type != REDIS_REPLY_STRING)
//			{
//				if (reply->type != REDIS_REPLY_NIL)
//				{
//					cout << "[ERROR]getString error reply type:" << reply->type << endl;
//				}
//				freeReplyObject(reply);
//				return "";
//			}
//
//			stringstream ss;
//			ss.write(reply->str, reply->len);
//			freeReplyObject(reply);
//			return ss.str();
//		}
//
//		bool setString(string key, string value)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "set %s %b", key.c_str(), value.c_str(), value.length());
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]setString checkReply failed." << endl;
//				return false;
//			}
//
//			freeReplyObject(reply);
//			return true;
//		}
//
//		int64_t getInt(string key)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "get %s", key.c_str());
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]getInt checkReply failed." << endl;
//				return 0;
//			}
//			if (reply->type != REDIS_REPLY_STRING)
//			{
//				if (reply->type != REDIS_REPLY_NIL)
//				{
//					cout << "[ERROR]getInt error reply type:" << reply->type << endl;
//				}
//				freeReplyObject(reply);
//				return 0;
//			}
//
//			istringstream iss(reply->str);
//			int64_t ret = 0;
//			iss >> ret;
//			return ret;
//		}
//
//		bool setInt(string key, int64_t value)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "set %s %lld", key.c_str(), value);
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]setInt checkReply failed." << endl;
//				return false;
//			}
//
//			freeReplyObject(reply);
//			return true;
//		}
//
//		string hgetString(string table, string key)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "hget %s %s", table.c_str(), key.c_str());
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]hgetString checkReply failed." << endl;
//				return "";
//			}
//			if (reply->type != REDIS_REPLY_STRING)
//			{
//				if (reply->type != REDIS_REPLY_NIL)
//				{
//					cout << "[ERROR]hgetString error reply type:" << reply->type << endl;
//				}
//				freeReplyObject(reply);
//				return "";
//			}
//
//			stringstream ss;
//			ss.write(reply->str, reply->len);
//			freeReplyObject(reply);
//			return ss.str();
//		}
//
//		//string hgetStringFmt(const char* fmt, ...)
//		//{
//		//	//string cmd = "hget ";
//		//	//cmd += fmt;
//		//	//fmt = cmd.c_str();
//		//	va_list valist;
//		//	va_start(valist, fmt);
//		//	redisReply* reply = (redisReply*)redisCommand(m_connect, fmt, valist);
//		//	va_end(valist);
//		//	if (!checkReply(reply))
//		//	{
//		//		cout << "[ERROR]hgetString checkReply failed." << endl;
//		//		return "";
//		//	}
//		//	if (reply->type != REDIS_REPLY_STRING)
//		//	{
//		//		if (reply->type != REDIS_REPLY_NIL)
//		//		{
//		//			cout << "[ERROR]hgetString error reply type:" << reply->type << endl;
//		//		}
//		//		freeReplyObject(reply);
//		//		return "";
//		//	}
//
//		//	stringstream ss;
//		//	ss.write(reply->str, reply->len);
//		//	freeReplyObject(reply);
//		//	return ss.str();
//		//}
//
//		//redisReply* cmd(const char* fmt, ...)
//		//{
//		//	// TODO:这个接口测试不通过，功能调用有问题
//		//	va_list valist;
//		//	va_start(valist, fmt);
//		//	redisReply* reply = (redisReply*)redisCommand(m_connect, fmt, valist);
//		//	va_end(valist);
//		//	if (!checkReply(reply))
//		//	{
//		//		cout << "[ERROR]cmd checkReply failed." << endl;
//		//		return nullptr;
//		//	}
//
//		//	return reply;
//		//}
//
//		bool hsetString(string table, string key, string value)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "hset %s %s %b", table.c_str(), key.c_str(), value.c_str(), value.length());
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]getString checkReply failed." << endl;
//				return false;
//			}
//
//			freeReplyObject(reply);
//			return true;
//		}
//
//		int64_t hgetInt(string table, string key)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "hget %s %s", table.c_str(), key.c_str());
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]hgetInt checkReply failed." << endl;
//				return 0;
//			}
//			if (reply->type != REDIS_REPLY_STRING)
//			{
//				if (reply->type != REDIS_REPLY_NIL)
//				{
//					cout << "[ERROR]hgetInt error reply type:" << reply->type << endl;
//				}
//				freeReplyObject(reply);
//				return 0;
//			}
//
//			istringstream iss(reply->str);
//			int64_t ret = 0;
//			iss >> ret;
//			return ret;
//		}
//
//		bool hsetInt(string table, string key, int64_t value)
//		{
//			redisReply* reply = (redisReply*)redisCommand(m_connect, "hset %s %s %lld", table.c_str(), key.c_str(), value);
//			if (!checkReply(reply))
//			{
//				cout << "[ERROR]hsetInt checkReply failed." << endl;
//				return false;
//			}
//
//			freeReplyObject(reply);
//			return true;
//		}
//
//	private:
//		bool checkReply(redisReply* reply)
//		{
//			if (m_connect == nullptr)
//			{
//				cout << "[ERROR]m_connect == nullptr" << endl;
//				return false;
//			}
//
//			if (m_connect->err != 0)
//			{
//				cout << "[ERROR]ErrorCode:" << m_connect->err << ", ErrorString:" << m_connect->errstr << endl;
//				if (reply != nullptr)
//				{
//					freeReplyObject(reply);
//				}
//				reconnect();
//				return false;
//			}
//			if (reply == nullptr)
//			{
//				cout << "[ERROR]m_reply == nullptr" << endl;
//				return false;
//			}
//
//			return true;
//		}
//
//		bool reconnect()
//		{
//			if (m_connect != nullptr)
//			{
//				redisFree(m_connect);
//				m_connect = nullptr;
//			}
//			return connect();
//		}
//
//	private:
//		redisContext* m_connect = nullptr;
//		string m_host = "";
//		int m_port = 0;
//	};
//}
