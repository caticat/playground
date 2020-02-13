#include "test_random.h"

namespace test_random
{
	CRandom::CRandom()
	{
		m_seed = 1;
	}

	uint32_t CRandom::Random()
	{
		uint32_t next = m_seed;
		uint32_t result;

		next *= 1103515245;
		next += 12345;
		result = (uint32_t)(next / 65536) % 2048;

		next *= 1103515245;
		next += 12345;
		result <<= 10;
		result ^= (uint32_t)(next / 65536) % 1024;

		next *= 1103515245;
		next += 12345;
		result <<= 10;
		result ^= (uint32_t)(next / 65536) % 1024;

		m_seed = next;
		return result;
	}

	uint32_t CRandom::Random(uint32_t unRange)
	{
		if (unRange == 0)
		{
			return 0;
		}
		return Random() % unRange;
	}

	uint32_t CRandom::Random(uint32_t unMinRange, uint32_t unMaxRange)
	{
		if (unMinRange == unMaxRange)
		{
			return unMaxRange;
		}

		return Random(unMaxRange - unMinRange) + unMinRange;
	}

	void test()
	{
		CRandom r;
		cout << "随机：" << r.Random() << endl;
		cout << "随机：" << r.Random() << endl;
		cout << "随机：" << r.Random() << endl;
		cout << "随机：" << r.Random() << endl;
		cout << "随机：" << r.Random() << endl;
	}
}