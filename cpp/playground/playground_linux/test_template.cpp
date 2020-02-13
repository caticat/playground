#include "test_template.h"
#include "ObjectPool.h"

namespace test_template
{
	void test()
	{
		TB<C> tb;
		C* c = tb.newT();
		c->test();
		delete c;

		//CObjectPool<C> op;
		//C* c = op.Alloc();
		//c->test();
		//op.Free(c);
	}
}