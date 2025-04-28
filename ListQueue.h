#pragma once

#include "queue.h"
#include "LinkedList.h"
#include "errors.h"

template <class T>
class ListQueue : public Queue<T>
{
private:
    LinkedList<T>* list;

public:
    ListQueue()
        : list(new LinkedList<T>()) {}

    ListQueue(const ListQueue& other)
        : list(new LinkedList<T>(*other.list)) {}

    ~ListQueue() override {
        delete list;
    }

    void Enqueue(const T& item) override {
        list->Append(item);
    }

    T Dequeue() override {
        if (IsEmpty()){
            throw MyException(ErrorType::OutOfRange, 5);
        }
        T value = list->GetFirst();
        list->RemoveAt(0);
        return value;
    }

    T& GetFront() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);

        return list->GetFirst();
    }

    const T& GetFront() const override {
        return const_cast<ListQueue*>(this)->GetFront();
    }

    T& GetRear() override {
        if (IsEmpty())
            throw MyException(ErrorType::OutOfRange, 5);

        return list->GetLast();
    }

    const T& GetRear() const override {
        return const_cast<ListQueue*>(this)->GetRear();
    }

    bool IsEmpty() const override {
        return list->GetLength() == 0;
    }

    bool IsFull() const override {
        //ну а как иначе)
        return false;
    }

    std::size_t Size() const override {
        return static_cast<std::size_t>(list->GetLength());
    }

    void Clear() override {
        list->Clear();
    }

    Queue<T>* Concat(const Queue<T>& other) const override {
        auto* result = new ListQueue<T>(*this);

        std::unique_ptr<Queue<T>> tmp(other.Clone());
        while (!tmp->IsEmpty())
            result->Enqueue(tmp->Dequeue());

        return result;
    }

    Queue<T>* Subqueue(std::size_t start, std::size_t end) const override {
        if (start > end || end >= Size()) {
            throw MyException(ErrorType::OutOfRange, 4);
        }
        auto* sub = new ListQueue<T>();
        for (std::size_t i = start; i <= end; ++i)
            sub->Enqueue(list->Get(static_cast<int>(i)));

        return sub;
    }

    const char* TypeName() const override {
        return "ListQueue";
    }

    Queue<T>* Clone() const override {
        return new ListQueue<T>(*this);
    }
};
