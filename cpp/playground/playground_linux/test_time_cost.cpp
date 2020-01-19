#include "test_time_cost.h"

namespace test_time_cost
{
	CTimeCostSimple::CTimeCostSimple()
	{
		Reset();
	}

	CTimeCostSimple::~CTimeCostSimple()
	{
		Check();
	}

	void CTimeCostSimple::Reset()
	{
		Begin();
		m_lastCost = 0;
		m_max = 0;
	}

	void CTimeCostSimple::Begin()
	{
		struct timeval tm;
		tm.tv_sec = 0;
		tm.tv_usec = 0;
		gettimeofday(&tm, nullptr);
		m_begin = tm.tv_sec * 1000000 + tm.tv_usec;
	}

	bool CTimeCostSimple::Check()
	{
		struct timeval tm;
		tm.tv_sec = 0;
		tm.tv_usec = 0;
		gettimeofday(&tm, nullptr);
		uint64_t cur = tm.tv_sec * 1000000 + tm.tv_usec;
		m_lastCost = cur - m_begin;
		m_begin = cur;

		std::cout << "消耗时间:" << m_lastCost << "微秒" << std::endl;

		if (m_lastCost > m_max)
		{
			m_max = m_lastCost;
			return true;
		}

		return false;
	}

	void testSimple()
	{
		CTimeCostSimple cost;
		for (int i = 0; i < 100000; i++)
		{
			if (i == 60000)
			{
				if (cost.Check())
				{
					std::cout << "产生消耗极值:" << cost.LastCost() << std::endl;
				}
			}
		}

		cost.Check();
		std::cout << "最后一次值:" << cost.LastCost() << ",最大值:" << cost.Max() << std::endl;
	}

	void test_1()
	{
		static CTimeCostData data;
		CTimeCost cost(data);
		for (int i = 0; i < 10000; i++)
		{ }
	}
	void test()
	{
		test_1();
		test_1();
		test_1();
		test_1();
		test_1();
	}
}