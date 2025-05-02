#pragma once
#include "queue.h"
#include "DynamicArray.h"
#include "errors.h"

template<class T>
class ArrayQueue : public Queue<T>
{
private:
    DynamicArray<T>* items;
    std::size_t count;

public:
    ArrayQueue()
        : items(new DynamicArray<T>(4)),
          count(0)
    {}

    ArrayQueue(const ArrayQueue& other)
        : items(new DynamicArray<T>(other.items->GetSize())),
          count(other.count)
    {
        for (std::size_t i = 0; i < count; ++i){
            items->Set(i, (*other.items)[i]);
        }
    }

    ~ArrayQueue() override {
        delete items;
    }

    void Enqueue(const T& value) override {
        if (count == items->GetSize()){
            std::size_t newCap = items->GetSize() * 2;
            auto* tmp = new DynamicArray<T>(newCap);

            for (std::size_t i = 0; i < count; ++i){
                tmp->Set(i, (*items)[i]);
            }
            delete items;
            items = tmp;
        }

        items->Set(count, value);
        count++;
    }

    T Dequeue() override {
        if (IsEmpty()){
            throw MyException(ErrorType::OutOfRange, 5);
        }
        T front = items->Get(0);

        for (std::size_t i = 1; i < count; ++i) {
            items->Set(i - 1, items->Get(i));
        }
        count--;
        return front;
    }

    T& GetFront() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);
        return (*items)[0];
    }

    const T& GetFront() const override {
        return const_cast<ArrayQueue*>(this)->GetFront();
    }
    
    bool IsEmpty() const override{
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
        return "ArrayQueue";
    }

    Queue<T>* Clone() const override
    {
        return new ArrayQueue<T>(*this);
    }
};
