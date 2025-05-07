#pragma once
#include "Queue.h"
#include "ArraySequence.h"
#include "errors.h"
#include <functional>

template<class T, class Compare = std::less<T>>
class ArrayPQueue : public Queue<T> {
    ArraySequence<T>* heap;
    Compare cmp;
public:
    ArrayPQueue() : heap(new ArraySequence<T>()) {}
    ArrayPQueue(const ArrayPQueue& other)
        : heap(new ArraySequence<T>(*other.heap)), cmp(other.cmp) {}

    ~ArrayPQueue() override { delete heap; }

    static std::size_t parent(std::size_t i) {
        return (i-1)>>1;
    }
    static std::size_t l  (std::size_t i) {
        return 2*i+1;
    }
    static std::size_t r (std::size_t i) {
        return 2*i+2;
    }

    void siftUp(std::size_t i) {
        while (i>0 && cmp((*heap)[parent(i)], (*heap)[i])) {
            std::swap((*heap)[i], (*heap)[parent(i)]);
            i = parent(i);
        }
    }
    void siftDown(std::size_t i) {
        while (true) {
            std::size_t best = i;
            if (l(i) < heap->GetLength() && cmp((*heap)[best], (*heap)[l(i)])) {
                best = l(i);
            }
            if (r(i) < heap->GetLength() && cmp((*heap)[best], (*heap)[r(i)])) {
                best = r(i);
            }
            if (best == i) {
                break;
            }
            std::swap((*heap)[i], (*heap)[best]);
            i = best;
        }
    }

    void Enqueue(const T& v) override {
        heap->Append(v);
        siftUp(heap->GetLength()-1);
    }
    T Dequeue() override {
        if (IsEmpty()) throw MyException(ErrorType::OutOfRange,5);
        T top = (*heap)[0];
        (*heap)[0] = (*heap)[heap->GetLength()-1];
        heap->RemoveAt(heap->GetLength()-1);
        if (!IsEmpty()) siftDown(0);
        return top;
    }

    T& GetFront() override {
        return (*heap)[0];
    }
    const T& GetFront() const override {
        return (*heap)[0];
    }

    bool IsEmpty() const override {
        return heap->Size() == 0;
    }
    bool IsFull()  const override {
        return false; // а как иначе?
    }
    std::size_t Size() const override {
        return heap->GetLength();
    }

    void Clear() override {
        heap->Clear();
    }

    const char* TypeName() const override {
        return "ArrayPQueue(heap)";
    }
    Queue<T>* Clone() const override {
        return new ArrayPQueue<T>(*this);
    }

};
