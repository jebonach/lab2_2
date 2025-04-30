#pragma once
#include "queue.h"
#include "DynamicArray.h"
#include "errors.h"

template <class T>
class CircularArrayQueue : public Queue<T>
{
private:
    DynamicArray<T>* items;
    std::size_t head;
    std::size_t tail;
    std::size_t count;
    std::size_t capacity;

    void grow() {
        std::size_t newCap = capacity * 2;
        auto* tmp = new DynamicArray<T>(newCap);

        for (std::size_t i = 0; i < count; ++i) {
            tmp->Set(i, items->Get((head + i) % capacity));
        }

        delete items;
        items = tmp;
        head = 0;
        tail = count;
        capacity = newCap;
    }

public:
    CircularArrayQueue(std::size_t initCap = 8)
        : items(new DynamicArray<T>(initCap)),
          head(0),
          tail(0),
          count(0),
          capacity(initCap){}

    CircularArrayQueue(const CircularArrayQueue& other)
        : items(new DynamicArray<T>(other.capacity)),
          head(0),
          tail(0),
          count(0),
          capacity(other.capacity){
        for (std::size_t i = 0; i < other.count; ++i) {
            Enqueue(other.items->Get((other.head + i) % other.capacity));
        }
    }

    ~CircularArrayQueue() override {
        delete items;
    }

    void Enqueue(const T& value) override{
        if (count == capacity){
            grow();
        }

        items->Set(tail, value);
        tail = (tail + 1) % capacity;
        ++count;
    }

    T Dequeue() override {
        if (IsEmpty()) {
            throw MyException(ErrorType::OutOfRange, 5);
        }

        T front = items->Get(head);
        head = (head + 1) % capacity;
        --count;
        return front;
    }

    T& GetFront() override {
        if (IsEmpty()){
            throw MyException(ErrorType::OutOfRange, 5);
        }
        return (*items)[head];
    }

    const T& GetFront() const override {
        return const_cast<CircularArrayQueue*>(this)->GetFront();
    }

    T& GetRear() override {
        if (IsEmpty()) {
            throw MyException(ErrorType::OutOfRange, 5);
        }
        return (*items)[(tail + capacity - 1) % capacity];
    }

    const T& GetRear() const override {
        return const_cast<CircularArrayQueue*>(this)->GetRear();
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
        head = tail = count = 0;
    }

    const char* TypeName() const override {
        return "CircularArrayQueue";
    }

    Queue<T>* Clone() const override {
        return new CircularArrayQueue<T>(*this);
    }
};
