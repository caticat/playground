#pragma once

#include <stdint.h>
#include <iostream>
#include <sys/time.h>

namespace test_time_cost
{
	class CTimeCostSimple
	{
	public:
		CTimeCostSimple();
		~CTimeCostSimple();
		void Reset();
		void Begin();
		bool Check(); // @return 是否产生新的最大值
		uint64_t LastCost() { return m_lastCost; }
		uint64_t Max() { return m_max; }
	private:
		uint64_t m_begin = 0;
		uint64_t m_lastCost = 0;
		uint64_t m_max = 0;
	};

	class CTimeCostData
	{
	public:
		bool Check(uint64_t cost)
		{
			std::cout << "消耗时间:" << cost << std::endl;
			m_last = cost;
			if (cost > m_max)
			{
				m_max = cost;
				std::cout << "变更最大值了,最大值:" << m_max << std::endl;
				return true;
			}
			return false;
		}
		uint64_t LastCost() { return m_last; }
		uint64_t Max() { return m_max; }
	private:
		uint64_t m_last = 0;
		uint64_t m_max = 0;
	};

	class CTimeCost
	{
	public:
		CTimeCost(CTimeCostData& data) : m_data(data)
		{
			struct timeval tm;
			tm.tv_sec = 0;
			tm.tv_usec = 0;
			gettimeofday(&tm, nullptr);
			m_begin = tm.tv_sec * 1000000 + tm.tv_usec;
		}
		~CTimeCost()
		{
			struct timeval tm;
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

	void testSimple();
	void test();
}
