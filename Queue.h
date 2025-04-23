#pragma once
#include <cstddef>

template<class T>
class Queue {
public:

    virtual void Enqueue(const T& item) = 0;
    virtual T Dequeue() = 0;

    virtual T& GetFront() = 0;
    virtual const T& GetFront() const = 0;

    virtual T& GetRear() = 0;
    virtual const T& GetRear() const = 0;

    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual std::size_t Size() const = 0;
    virtual void Clear() = 0;

    virtual Queue<T>* Concat(const Queue<T>& other) const = 0;
    virtual Queue<T>* Subqueue(std::size_t start, std::size_t end) const = 0;
    // virtual bool ContainsSubqueue() const = 0;
    // virtual std::pair<Queue<T>*, Queue<T>*> Split() const = 0;

    // virtual Queue<T>* Where() const = 0;
    // virtual Queue<T>* Map() const = 0;
    // virtual T Reduce() const = 0;

    virtual ~Queue() = default;
    virtual const char* TypeName() const = 0;
    virtual Queue<T>* Clone() const = 0;
};