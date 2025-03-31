#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* items;

public:
    ArraySequence() {
        items = new DynamicArray<T>(0);
    }

    ArraySequence(T* arr, int count) {
        items = new DynamicArray<T>(arr, count);
    }

    ArraySequence(std::initializer_list<T> list) {
        items = new DynamicArray<T>(list);
    }

    ArraySequence(const ArraySequence<T>& other) {
        items = new DynamicArray<T>(*other.items);
    }

    virtual ~ArraySequence() {
        delete items;
    }

    virtual T GetFirst() const override {
        if (items->GetSize() == 0) {
            throw std::out_of_range("ArraySequence::GetFirst() - sequence is empty(upset)");
        }
        return items->Get(0);
    }

    virtual T GetLast() const override {
        int size = items->GetSize();
        if (size == 0) {
            throw std::out_of_range("ArraySequence::GetLast() - sequence is empty(upset)");
        }
        return items->Get(size - 1);
    }

    virtual T Get(int index) const override {
        return items->Get(index);
    }

    virtual int GetLength() const override {
        return items->GetSize();
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex ||
            endIndex >= items->GetSize()) {
            throw std::out_of_range("ArraySequence::GetSubsequence() - index out of range(unluck)");
        }
        int newSize = endIndex - startIndex + 1;
        auto* subArr = new T[newSize];
        for (int i = 0; i < newSize; i++) {
            subArr[i] = items->Get(startIndex + i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(subArr, newSize);
        delete[] subArr;
        return result;
    }

    virtual Sequence<T>* Append(const T& item) override {
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, item);
        return this;
    }

    virtual Sequence<T>* Prepend(const T& item) override {
        items->Resize(items->GetSize() + 1);
        for (int i = items->GetSize() - 1; i > 0; i--) {
            items->Set(i, items->Get(i - 1));
        }
        items->Set(0, item);
        return this;
    }

    virtual Sequence<T>* InsertAt(const T& item, int index) override {
        if (index < 0 || index > items->GetSize()) {
            throw std::out_of_range("ArraySequence::InsertAt() - index out of range(unluck)");
        }
        items->Resize(items->GetSize() + 1);
        for (int i = items->GetSize() - 1; i > index; i--) {
            items->Set(i, items->Get(i - 1));
        }
        items->Set(index, item);
        return this;
    }

    virtual Sequence<T>* Concat(const Sequence<T>* seq) const override {
        int size1 = this->GetLength();
        int size2 = seq->GetLength();
        int newSize = size1 + size2;
        T* newArr = new T[newSize];
        for (int i = 0; i < size1; i++) {
            newArr[i] = items->Get(i);
        }
        for (int i = 0; i < size2; i++) {
            newArr[size1 + i] = seq->Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(newArr, newSize);
        delete[] newArr;
        return result;
    }

    virtual Sequence<T>* Clone() const override {
        return new ArraySequence<T>(*this);
    }
};
