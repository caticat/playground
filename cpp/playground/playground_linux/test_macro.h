#pragma once
#include <string>
#include <sys/time.h>

using namespace std;

namespace test_macro
{

#define CALC_TIME_COST(NAME, LOG, TOLERANCE) static CTimeCostData NAME##Data(LOG, TOLERANCE);\
CTimeCost NAME(NAME##Data);
#define CALC_TIME_COST_DEFAULT(NAME, LOG) static CTimeCostData NAME##Data(LOG);\
CTimeCost NAME(NAME##Data);
	/**
	* @brief
	* 时间消耗检测数据记录
	*/
	class CTimeCostData
	{
	public:
		CTimeCostData(string prefix, uint64_t tolerance = 200)
		{
			m_fmt = prefix + ":cost:%llu, max:%llu, average:%llu(microsecond), counter:%llu\n";
			m_tolerance = tolerance;
		}
		void Check(uint64_t cost)
		{
			++m_counter;
			m_total += cost;
			if (cost > m_max)
			{
				m_max = cost;
			}
			if (cost >= m_tolerance)
			{
				printf(m_fmt.c_str(), cost, m_max, (m_total / m_counter), m_counter);
			}
		}
		timeval& GetTM() { return m_tm; }
	private:
		uint64_t m_counter = 0;
		uint64_t m_total = 0;
		uint64_t m_max = 0;
		uint64_t m_tolerance; // 容忍值，超过才会有输出
		string m_fmt = "";
		timeval m_tm;
	};

	/**
	* @brief
	* 时间消耗检测
	*/
	class CTimeCost
	{
	public:
		CTimeCost(CTimeCostData& data) : m_data(data)
		{
			timeval& tm = m_data.GetTM();
			tm.tv_sec = 0;
			tm.tv_usec = 0;
			gettimeofday(&tm, nullptr);
			m_begin = tm.tv_sec * 1000000 + tm.tv_usec;
		}
		~CTimeCost()
		{
			timeval& tm = m_data.GetTM();
			tm.tv_sec = 0;
			tm.tv_usec = 0;
			gettimeofday(&tm, nullptr);
			uint64_t cur = tm.tv_sec * 1000000 + tm.tv_usec;
			m_data.Check(cur - m_begin);
		}
	private:
		CTimeCostData& m_data;
		uint64_t m_begin = 0;
	};

	void test();
}
