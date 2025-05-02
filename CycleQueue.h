#pragma once
#include "Queue.h"
#include "DynamicArray.h"
#include "errors.h"

template<class T>
class CircularArrayQueue : public Queue<T>
{
private:
    DynamicArray<T>* items;
    std::size_t head;
    std::size_t tail;
    std::size_t count;

    void grow() {
        std::size_t oldCap = items->GetSize();
        std::size_t newCap = oldCap * 2;

        auto* tmp = new DynamicArray<T>(newCap);
        for (std::size_t i = 0; i < count; ++i){
            tmp->Set(i, items->Get((head + i) % oldCap));
        }
        delete items;
        items = tmp;
        head = 0;
        tail = count;
    }

public:
    explicit CircularArrayQueue(std::size_t initCap = 8)
        : items(new DynamicArray<T>(initCap)),
          head(0), tail(0), count(0){}


    CircularArrayQueue(const CircularArrayQueue& other)
        : items(new DynamicArray<T>(other.items->GetSize())),
          head(0),
          tail(0),
          count(0)
    {
        for (std::size_t i = 0; i < other.count; ++i) {
            Enqueue(other.items->Get((other.head + i) % other.items->GetSize()));
        }
        count = other.count;
    }

    ~CircularArrayQueue() override {
        delete items;
    }

    void Enqueue(const T& value) override {
        if (count == items->GetSize())
            grow();

        items->Set(tail, value);
        tail = (tail + 1) % items->GetSize();
        ++count;
    }

    T Dequeue() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);

        T front = items->Get(head);
        head = (head + 1) % items->GetSize();
        count++;
        return front;
    }

    T& GetFront() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);
        return (*items)[head];
    }

    const T& GetFront() const override {
        return const_cast<CircularArrayQueue*>(this)->GetFront();
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
        head = tail = count = 0;
    }

    const char* TypeName() const override {
        return "CircularArrayQueue";
    }

    Queue<T>* Clone() const override {
        return new CircularArrayQueue<T>(*this);
    }
};
