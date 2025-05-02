#pragma once

#include "queue.h"
#include "DynamicArray.h"
#include "errors.h"
#include <functional> 

using Self = ArrayPQueueSorted<T, Compare>;

template<class T, class Compare = std::less<T>>
class ArrayPQueueSorted : public Queue<T>
{
private:
    DynamicArray<T>* items;
    std::size_t count;
    Compare cmp;

public:
    explicit ArrayPQueueSorted(std::size_t initCap = 8,
                               Compare comp = Compare{})
        : items(new DynamicArray<T>(initCap)),
          count(0),
          cmp(comp) {}

    ArrayPQueueSorted(const ArrayPQueueSorted& other)
        : items(new DynamicArray<T>(*other.items)),
          count(other.count),
          cmp(other.cmp) {}

    ~ArrayPQueueSorted() override { 
        delete items;
    }

    void Enqueue(const T& value) override{
        if (count == items->GetSize()){
            std::size_t newCap = items->GetSize() * 2;
            auto* tmp = new DynamicArray<T>(newCap);

            for (std::size_t i = 0; i < count; ++i){
                tmp->Set(i, (*items)[i]);
            }
            delete items;
            items = tmp;
        }

        std::size_t lo = 0, hi = count;
        while (lo < hi)
        {
            std::size_t mid = (lo + hi) / 2;
            if (higher(value, items->Get(mid)))
                hi = mid;
            else
                lo = mid + 1;
        }

        for (std::size_t i = count; i > lo; --i) {
            items->Set(i, items->Get(i - 1));
        }
        items->Set(lo, value);
        ++count;
    }

    T Dequeue() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);

        T top = items->Get(0);
        for (std::size_t i = 1; i < count; ++i)
            items->Set(i - 1, items->Get(i));
        --count;
        return top;
    }

    T& GetFront() override {
        if (IsEmpty()) {
            throw MyException(ErrorType::OutOfRange, 5);
        }
        return (*items)[0];
    }

    const T& GetFront() const override {
        return const_cast<Self*>(this)->GetFront();
    }


    bool IsEmpty() const override {
        return count == 0;
    }
    
    bool IsFull() const override {
        return count == items->GetSize();
    }

    std::size_t Size() const override {
        return count;
    }

    void Clear() override {
        count = 0;
    }

    const char* TypeName() const override {
        return "ArrayPQueueSorted";
    }

    Queue<T>* Clone() const override {
        return new Self(*this);
    }
};
