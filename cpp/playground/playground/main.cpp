/*
 * 测试代码用
 */

#include <iostream>
#include <list>

using std::cout;
using std::endl;

class CA;
void test_destroy_s1(CA* ca)
{
	free(ca);
	ca = NULL;
}
class CA
{
public:
	CA()
	{

	}

	~CA()
	{
		a = 998;
	}

	void dest()
	{
		test_destroy_s1(this);
	}

	int a;
};

void test_destroy()
{
	CA* ca = new CA;
	ca->a = 100;
	cout << "1:" << ca << "," << ca->a << endl;
	ca->dest();
	cout << "2:" << ca << "," << ca->a << endl;
}

void test_iter()
{
	std::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	for (auto i = l.begin(); i != l.end();)
	{
		cout << "print:" << *i << endl;
		if (*i == 3)
		{
			l.push_front(4);
			i = l.erase(i);
		}
		else
		{
			i++;
		}
		//if (l.size() < 5)
		//{
		//	l.push_back(5);
		//}
	}

	for (auto i : l)
	{
		cout << "end print:" << i << endl;
	}
}

int main()
{
	cout << "开始" << endl;

	//test_iter();
	test_destroy();

	cout << "结束" << endl;

	return 0;
}
