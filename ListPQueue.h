#pragma once

#include "Queue.h"
#include "LinkedList.h"
#include "errors.h"
#include <functional>

template <class T, class Compare = std::less<T>>
class ListPQueue : public Queue<T>
{
private:
    LinkedList<T>* list;
    Compare cmp;

    bool higher(const T& a, const T& b) const {
        return cmp(b, a);
    }

public:
    explicit ListPQueue(Compare comp = Compare{})
        : list(new LinkedList<T>()), cmp(comp)
    {}

    ListPQueue(const ListPQueue& other)
        : list(new LinkedList<T>(*other.list)), cmp(other.cmp)
    {}

    ~ListPQueue() override {
        delete list;
    }

    void Enqueue(const T& value) override {
        std::size_t pos = 0;
        int len = list->GetLength();

        while (pos < static_cast<std::size_t>(len) &&
               !higher(value, list->Get(static_cast<int>(pos)))) {
            ++pos;
        }

        if (pos == 0)
            list->Prepend(value);
        else if (pos == static_cast<std::size_t>(len))
            list->Append(value);
        else
            list->InsertAt(value, static_cast<int>(pos));
    }

    T Dequeue() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);

        T top = list->GetFirst();
        list->RemoveAt(0);
        return top;
    }

    T& GetFront() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);
        return list->GetFirst();
    }

    const T& GetFront() const override {
        return const_cast<ListPQueue*>(this)->GetFront();
    }

    bool IsEmpty() const override {
        return list->GetLength() == 0;
    }

    bool IsFull() const override {
        return false;
    }

    std::size_t Size() const override {
        return static_cast<std::size_t>(list->GetLength());
    }

    void Clear() override {
        list->Clear();
    }

    const char* TypeName() const override {
        return "ListPQueue";
    }

    Queue<T>* Clone() const override {
        return new ListPQueue<T, Compare>(*this);
    }
};