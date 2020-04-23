#include "test_map.h"

namespace test_map
{
	//void test_vec()
	//{
	//	vector<A> a;
	//	A b;
	//	b.a = 10;
	//	A c;
	//	c.a = 20;
	//	a.push_back(b);
	//	a.push_back(c);

	//	cout << "01_______________" << endl;
	//	vector<A> d = a;
	//	cout << "02_______________" << endl;
	//	vector<A>::iterator it = a.begin();
	//	it->a = 30;

	//	cout << "1_______________" << endl;
	//	for (vector<A>::iterator it = a.begin(); it != a.end(); ++it)
	//	{
	//		cout << it->a << endl;
	//	}
	//	cout << "2_______________" << endl;
	//	for (vector<A>::iterator it = d.begin(); it != d.end(); ++it)
	//	{
	//		cout << it->a << endl;
	//	}
	//	cout << "3_______________" << endl;
	//}

	void test_2()
	{
		map<int, map<int, int> > m;
		m[1][3] = 5;
		for (auto i = m.begin(); i != m.end(); ++i)
		{
			cout << i->first << endl;
			for (auto j = i->second.begin(); j != i->second.end(); ++j)
			{
				cout << "\t" << j->first << "->" << j->second << endl;
			}
		}
	}

	void test_copy()
	{
		B a;
		a.m_map[1] = 100;
		a.m_map[2] = 200;
		a.m_map[3] = 300;
		B b = a;
		a.m_map[2] = 20000;

		cout << "a:" << endl;
		for (map<int, int>::iterator it = a.m_map.begin(); it != a.m_map.end(); ++it)
		{
			cout << "\t" << it->first << "->" << it->second << endl;
		}

		cout << "b:" << endl;
		for (map<int, int>::iterator it = b.m_map.begin(); it != b.m_map.end(); ++it)
		{
			cout << "\t" << it->first << "->" << it->second << endl;
		}
	}

	void test()
	{
		test_copy();
	}
}
