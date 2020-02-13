// random测试
#pragma once
#include <iostream>

using namespace std;

namespace test_random
{
	class CRandom {
	public:
		CRandom();
		inline void SetSeed(uint32_t dwSeed)
		{
			m_seed = dwSeed;
		}

		inline uint32_t GetSeed() { return m_seed; }
		uint32_t Random();
		uint32_t Random(uint32_t unRange);
		uint32_t Random(uint32_t dwMin, uint32_t dwMax);
	private:
		uint32_t m_seed;
	};

	void test();
}
