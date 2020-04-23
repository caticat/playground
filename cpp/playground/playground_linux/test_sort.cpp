#include "test_sort.h"
#include <iostream>
#include <algorithm>
#include <map>

namespace test_sort
{
	using namespace std;

	int GetRoleEquipRefineLv(int* arr)
	{
		int arrRefineStarLen = 11;
		int arrRefineStar[10] = { 0 };
		for (int i = 1; i < arrRefineStarLen; i++)
		{
			arrRefineStar[i - 1] = arr[i - 1];
		}
		sort(arrRefineStar, arrRefineStar + 10);

		for (int i = 0; i < arrRefineStarLen - 1; i++)
		{
			cout << "->" << arrRefineStar[i] << endl;
		}

		return arrRefineStar[1];
	}

	void test()
	{
		int a[] = { 3, 1, 1, 0, 4, 2 };
		int aLen = int(sizeof(a) / sizeof(int));
		sort(a, a+ aLen);
		for (int i = 0; i < aLen; i++)
		{
			cout << a[i] << endl;
		}

		int b[3] = {};
		for (int i = 0; i < 3; i++)
		{
			cout << b[i] << endl;
		}

		int c[10] = { 3, 1, 1, 0, 4, 2, 5, 7, 3, 10 };
		cout << "abc:" << GetRoleEquipRefineLv(c) << endl;
	}
}
