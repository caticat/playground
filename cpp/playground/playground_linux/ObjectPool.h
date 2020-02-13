/*
 * ObjectPool.h
 *
 *  Created on: 2018年5月22日
 *      Author: youguozheng
 */

#ifndef BASE_OBJECTPOOL_H_
#define BASE_OBJECTPOOL_H_

#include <deque>
#include <vector>
#include <stdint.h>

template<typename T>
class ObjectAllocator
{
   enum
    {
        POOL_INFLATE_SIZE= 100,
    };
public:
    typedef size_t   size_type;
    typedef T*       pointer;
    typedef T&       reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef T        value_type;

    typedef std::deque<pointer> ObjectQueue;

    typedef typename ObjectQueue::iterator ObjectQueueItr;

    ObjectAllocator(int initSize = 0, int growSize = 1 ) throw()
     {
        m_totalSize =0;
        m_growSize = growSize;
        inflate(initSize );
     }


    ~ObjectAllocator() throw()
     {
        for(typename ObjectQueue::iterator itr = m_objects.begin(); itr != m_objects.end(); ++itr)
          {
            ::operator delete (*itr);
          }
        m_objects.clear();
     }

    pointer address(reference __x) const
     {
        return &__x;
     }

    const_pointer address(const_reference __x) const
     {
        return &__x;
     }

    T* allocate()
     {
        if (m_objects.empty())
        {
            this->inflate(m_growSize);
        }

        T * ret = m_objects.front();
        m_objects.pop_front();
        return ret;
     }

    // __p is not permitted to be a null pointer.
    void deallocate(pointer __p)
     {
        m_objects.push_back(__p);
     }

    inline size_type read_size()
     {
        return m_objects.size();
     }

    inline size_type write_size() const throw()
     {
        return m_objects.size() ;
     }

private:
    void inflate(int count = POOL_INFLATE_SIZE)
     {
        //NOTICE: locked outside
        for (int i = 0; i < count ; i++)
        {
            pointer  _p = static_cast<pointer>(::operator new (sizeof(value_type)));
            m_objects.push_back(_p);
        }
        m_totalSize += count;
     }

    template<typename T1>
    void operator = (const ObjectAllocator<T1>&) throw()
     {

     }

    ObjectQueue m_objects;
    int m_totalSize ;
    int m_growSize;
};

template <typename _Tp,
            typename _Alloc=ObjectAllocator<_Tp> >
class CObjectPool
{
public:
    CObjectPool(uint32_t dwInitCount = 0, uint32_t dwGrouCount = 1)
        :m_allocator(dwInitCount,dwGrouCount)
     {
     }

    inline _Tp*   Alloc()
     {
        return new (m_allocator.allocate())_Tp;
     }

    template<typename P1>
    _Tp *  Alloc(P1 p1)
     {
        return new (m_allocator.allocate())_Tp(p1);
     }

    template<typename P1,typename P2>
    _Tp*  Alloc(P1 p1,P2 p2)
     {
        return new (m_allocator.allocate())_Tp(p1,p2);
     }

    template<typename P1,typename P2,typename P3>
    _Tp*  Alloc(P1 p1,P2 p2,P3 p3)
     {
        return new (m_allocator.allocate())_Tp(p1,p2,p3);
     }

    template<typename P1,typename P2,typename P3,typename P4>
    _Tp*  Alloc(P1 p1,P2 p2,P3 p3,P4 p4)
     {
        return new (m_allocator.allocate())_Tp(p1,p2,p3,p4);
     }

    template<typename P1,typename P2,typename P3,typename P4,typename P5>
    _Tp*  Alloc(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
     {
        return new (m_allocator.allocate())_Tp(p1,p2,p3,p4,p5);
     }

    void  Free(_Tp * p)
     {
        p->~_Tp();
        m_allocator.deallocate(p);
     }

    _Alloc &  GetAllocator()
     {
        return m_allocator;
     }

private:
    _Alloc m_allocator;
};

#endif /* BASE_OBJECTPOOL_H_ */
