#pragma once
#include "Queue.h"
#include "DynamicArray.h"
#include <functional>

template<class T, class Cmp=std::less<T>>
class PQueueArray : public Queue<T> {
    private:
    auto cmp = [](int l, int r) { return l < r; };
    DynamicArray<T>* items;
    std::size_t count;
    std::size_t capacity;

public:
    explicit ArrayQueue(std::size_t initCap = 4)
        : items(new DynamicArray<T>(initCap)),
          count(0),
          capacity(initCap) {}

    ArrayQueue(const ArrayQueue& other)
        : items(new DynamicArray<T>(other.capacity)),
        count(other.count), capacity(other.capacity) {
        for (std::size_t i = 0; i < count; ++i) {
            items->Set(i, (*other.items)[i]);
        }
    }

    ~ArrayQueue() override {
        delete items;
    }

    void Enqueue(const T& value) override {
        if (count == capacity) {
            std::size_t newCap = capacity * 2;
            auto* tmp = new DynamicArray<T>(newCap);

            for (std::size_t i = 0; i < count; ++i) {
                tmp->Set(i, (*items)[i]);
            }

            delete items;
            items = tmp;
            capacity = newCap;
        }

        items->Set(count, value);
        ++count;
    }

    T Dequeue() override {
        if (IsEmpty()) {
            throw MyException(ErrorType::OutOfRange, 5);
        }
        T front = items->Get(0);

        for (std::size_t i = 1; i < count; ++i){
            items->Set(i - 1, items->Get(i));
        }
        --count;
        return front;
    }

    T& GetFront() override {
        if (IsEmpty())
        {
            throw MyException(ErrorType::OutOfRange, 5);
        }
        return (*items)[0];
    }

    const T& GetFront() const override {
        return const_cast<ArrayQueue*>(this)->GetFront();
    }

    bool IsEmpty() const override {
        return count == 0;
    }

    bool IsFull() const override {
        return count == capacity;
    }

    std::size_t Size() const override {
        return count;
    }

    void Clear() override {
        count = 0;
    }

    const char* TypeName() const override {
        return "ArrayQueue";
    }

    Queue<T>* Clone() const override {
        return new ArrayQueue<T>(*this);
    }

};