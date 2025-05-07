#pragma once
#include "Queue.h"
#include "ArraySequence.h"
#include "errors.h"

template<class T>
class ArrayQueue : public Queue<T>
{
private:
    ArraySequence<T>* items;

public:
    ArrayQueue() : items(new ArraySequence<T>()){}

    ArrayQueue(const ArrayQueue& other)
        : items(new ArraySequence<T>(*other.items)) {}

    ~ArrayQueue() override { delete items; }

    void Enqueue(const T& v) override {
        items->Append(v);
    }

    T Dequeue() override {
        if (IsEmpty()) throw MyException(ErrorType::OutOfRange,5);
        T front = items->GetFirst();
        items->RemoveAt(0);
        return front;
    }

    T& GetFront() override {
        return (*items)[0];
    }
    const T& GetFront() const override {
        return (*items)[0];
    }

    bool IsEmpty() const override {
        return items->GetLength() == 0;
    }
    bool IsFull () const override {
        return false;
    }
    std::size_t Size() const override {
        return items->GetLength();
    }

    void Clear() override {
        items->Clear();
    }

    const char* TypeName() const override {
        return "ArrayQueue";
    }

    Queue<T>* Clone() const override {
        return new ArrayQueue<T>(*this);
    }

};
