#pragma once
#include "Queue.h"
#include "DynamicArray.h"
#include "how_to_train_your_exception.h"

template<class T>
class ArrayQueue : public Queue<T> {
    DynamicArray<T>* items;
    std::size_t head, tail, count, capacity;

    void ensureCapacity() {
        if (count < capacity) return;
        std::size_t newCap = capacity * 2;
        DynamicArray<T>* newArr = new DynamicArray<T>(newCap);
        for (std::size_t i = 0; i < count; ++i) {
            newArr->Set(i, items->Get((head + i) % capacity));
        }
        delete items;
        items = newArr;
        head = 0;
        tail = count;
        capacity = newCap;
    }

public:
    ArrayQueue() : head(0), tail(0), count(0), capacity(4) {
        items = new DynamicArray<T>(capacity);
    }
    ArrayQueue(const ArrayQueue& other) : head(0), tail(0), count(0), capacity(other.capacity) {
        items = new DynamicArray<T>(capacity);
        for (std::size_t i = 0; i < other.count; ++i) {
            Enqueue(other.items->Get((other.head + i) % other.capacity));
        }
    }
    ~ArrayQueue() override { delete items; }

    void Enqueue(const T& item) override {
        ensureCapacity();
        items->Set(tail, item);
        tail = (tail + 1) % capacity;
        ++count;
    }

    T Dequeue() override {
        if (IsEmpty()) throw std::out_of_range("Empty queue");
        T result = items->Get(head);
        head = (head + 1) % capacity;
        --count;
        return result;
    }

    T& GetFront() override {
        if (IsEmpty()) throw std::out_of_range("Empty queue");
        return items->operator[](head);
    }
    const T& GetFront() const override {
        return const_cast<ArrayQueue*>(this)->GetFront();
    }

    T& GetRear() override {
        if (IsEmpty()) throw std::out_of_range("Empty queue");
        return items->operator[]((tail + capacity - 1) % capacity);
    }
    const T& GetRear() const override {
        return const_cast<ArrayQueue*>(this)->GetRear();
    }

    bool IsEmpty() const override { return count == 0; }
    bool IsFull() const override { return count == capacity; }

    std::size_t Size() const override { return count; }
    void Clear() override { head = tail = count = 0; }

    Queue<T>* Clone() const override { return new ArrayQueue<T>(*this); }
    const char* TypeName() const override { return "ArrayQueue"; }

    Queue<T>* Where(bool (*predicate)(const T&)) const override {
        auto* res = new ArrayQueue<T>();
        for (std::size_t i = 0; i < count; ++i) {
            T val = items->Get((head + i) % capacity);
            if (predicate(val)) res->Enqueue(val);
        }
        return res;
    }

    Queue<T>* Map(T (*f)(const T&)) const override {
        auto* res = new ArrayQueue<T>();
        for (std::size_t i = 0; i < count; ++i) {
            res->Enqueue(f(items->Get((head + i) % capacity)));
        }
        return res;
    }

    T Reduce(T (*f)(const T&, const T&), T init) const override {
        for (std::size_t i = 0; i < count; ++i) {
            init = f(init, items->Get((head + i) % capacity));
        }
        return init;
    }

    Queue<T>* Concat(const Queue<T>& other) const override {
        auto* result = new ArrayQueue<T>(*this);
        auto* otherClone = other.Clone();
        while (!otherClone->IsEmpty()) result->Enqueue(otherClone->Dequeue());
        delete otherClone;
        return result;
    }

    Queue<T>* Subqueue(std::size_t start, std::size_t end) const override {
        if (start > end || end >= count) throw std::out_of_range("Invalid range");
        auto* res = new ArrayQueue<T>();
        for (std::size_t i = start; i <= end; ++i) {
            res->Enqueue(items->Get((head + i) % capacity));
        }
        return res;
    }

    bool ContainsSubqueue(const Queue<T>& sub) const override {
        auto* s = sub.Clone();
        std::vector<T> subElems;
        while (!s->IsEmpty()) subElems.push_back(s->Dequeue());
        delete s;
        if (subElems.empty() || subElems.size() > count) return false;
        for (std::size_t i = 0; i <= count - subElems.size(); ++i) {
            bool match = true;
            for (std::size_t j = 0; j < subElems.size(); ++j) {
                if (!(items->Get((head + i + j) % capacity) == subElems[j])) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }

    std::pair<Queue<T>*, Queue<T>*> Split(bool (*predicate)(const T&)) const override {
        auto* a = new ArrayQueue<T>();
        auto* b = new ArrayQueue<T>();
        for (std::size_t i = 0; i < count; ++i) {
            T val = items->Get((head + i) % capacity);
            (predicate(val) ? a : b)->Enqueue(val);
        }
        return {a, b};
    }
};