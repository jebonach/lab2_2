#include <iostream>
#include <chrono>
#include <string>
#include <vector>

#include <iomanip>
#include "ArrayQueue.h"
#include "CycleQueue.h"
#include "ListQueue.h"
#include "ArrayPQueue.h"
#include "ListPQueue.h"

using clk = std::chrono::high_resolution_clock;
using ms = std::chrono::duration<double, std::milli>;


struct Result { 
    std::string name; 
    double enq_ms, deq_ms;
};

template<class Q>
Result bench_fifo(const std::string& name, std::size_t N) {
    Q q;
    auto t0 = clk::now();
    for (std::size_t i = 0; i < N; ++i) q.Enqueue(static_cast<int>(i));
    auto t1 = clk::now();
    for (std::size_t i = 0; i < N; ++i) q.Dequeue();
    auto t2 = clk::now();

    return { name, ms(t1 - t0).count(), ms(t2 - t1).count() };
}


template<class PQ>
Result bench_pq(const std::string& name, std::size_t N) {
    PQ pq;
    auto t0 = clk::now();
    for (std::size_t i = 0; i < N; ++i) pq.Enqueue(static_cast<int>(i));
    auto t1 = clk::now();
    for (std::size_t i = 0; i < N; ++i) pq.Dequeue();
    auto t2 = clk::now();

    return { name, ms(t1 - t0).count(), ms(t2 - t1).count() };
}

int main()
{
    std::size_t N;
    std::cin >> N;
    std::vector<Result> tbl;
    tbl.push_back(bench_fifo<ArrayQueue<int>> ("ArrayQueue", N));
    tbl.push_back(bench_fifo<CircularArrayQueue<int>>("CircularArrayQueue", N));
    tbl.push_back(bench_fifo<ListQueue<int>> ("ListQueue", N));
    tbl.push_back(bench_pq <ArrayPQueue<int>> ("ArrayPQueue", N));
    tbl.push_back(bench_pq <ListPQueue<int>> ("ListPQueue", N));

    std::cout << "\n==== Queue benchmark (" << N << " enq + deq) ====\n";
    std::cout << "\n                enqueue [ms]   dequeue [ms]\n";
    std::cout << "-------------------------------------------\n";
    for (const auto& r : tbl)
        std::cout << std::left << std::setw(20) << r.name
                  << std::right<< std::setw(10) << r.enq_ms
                  << std::setw(14) << r.deq_ms << "\n";
    return 0;
}
