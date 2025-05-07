#include "errors.h"
#include <cassert>
#include <iostream>

#include <chrono>
#include "ArrayQueue.h"
#include "CycleQueue.h"
#include "ListQueue.h"
#include "ArrayPQueue.h"
#include "ListPQueue.h"

template<class Q>
void drain(Q& q, std::initializer_list<int> pattern)
{
    assert(q.Size() == pattern.size());
    for (int v : pattern) {
        assert(!q.IsEmpty());
        int got = q.Dequeue();
        assert(got == v);
    }
    assert(q.IsEmpty());
}

template<class Q>
void test_fifo_basic()
{
    Q q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    assert(q.GetFront() == 1);
    drain(q,{1,2,3});
}

template<class Q>
void test_fifo_grow()
{
    Q q;
    for (int i = 0; i < 256; ++i) {
        q.Enqueue(i);
    }
    for (int i = 0; i < 256; ++i) {
        assert(q.Dequeue() == i);
    }
    assert(q.IsEmpty());
}

template<class Q>
void test_concat_subqueue()
{
    Q a;
    for (int v : {1,2,3}) {
        a.Enqueue(v);
    }
    Q b;
    for (int v : {4,5}) {
        b.Enqueue(v);
    }
    
    Q* ab = static_cast<Q*>(a.Concat(b));
    drain(*ab,{1,2,3,4,5});
    delete ab;

    Q* sub = static_cast<Q*>( a.Subqueue(1,2) );
    drain(*sub,{2,3});
    delete sub;
}

template<class PQ>
void test_pq_basic()
{
    PQ pq;
    pq.Enqueue(15);
    pq.Enqueue(40);
    pq.Enqueue(5);
    pq.Enqueue(25);
    assert(pq.GetFront() == 40);
    drain(pq,{40,25,15,5});
}

int main()
{
    std::cout << "[ queue-tests ]\n";

    const auto start{std::chrono::steady_clock::now()};
    test_fifo_basic<ArrayQueue<int>>();
    const auto finish{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> AQB {finish - start};


    test_fifo_basic<ArrayQueue<int>>();
    test_fifo_basic<CircularArrayQueue<int>>();
    test_fifo_basic<ListQueue<int>>();

    test_fifo_grow<ArrayQueue<int>>();
    test_fifo_grow<CircularArrayQueue<int>>();
    test_fifo_grow<ListQueue<int>>();

    test_concat_subqueue<ArrayQueue<int>>();
    test_concat_subqueue<CircularArrayQueue<int>>();
    test_concat_subqueue<ListQueue<int>>();

    test_pq_basic<ArrayPQueue<int>>();
    test_pq_basic<ListPQueue<int>>();

    std::cout << "Queue tests passed successfully!\n\n";
    return 0;
}
