#pragma once
#include "DynamicArray.h"
#include "Sequence.h"
#include <stdexcept>
#include "how_to_train_your_exception.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;
    int count;
    int capacity;

public:
    ArraySequence() {
        capacity = 4;
        items = new DynamicArray<T>(capacity);
        count = 0;
    }

    ArraySequence(const T* arr, int length) {
        if (length < 0) {
            throw MyException(ErrorType::NegativeSize, 0);
        }
        
        capacity = (length > 0) ? (2*length) : 1;
        items = new DynamicArray<T>(capacity);
        for (int i = 0; i < length; i++) {
            items->Set(i, arr[i]);
        }
        count = length;
    }

    ArraySequence(const ArraySequence<T>& other) {
        capacity = other.capacity;
        count = other.count;
        items = new DynamicArray<T>(*other.items);
    }

    virtual ~ArraySequence() {
        delete items;
    }

    virtual T GetFirst() const override {
        if (items->GetSize() == 0) {
            throw MyException(ErrorType::OutOfRange, 2);
        }
        return items->Get(0);
    }

    virtual T GetLast() const override {
        if (count == 0) {
            throw MyException(ErrorType::OutOfRange, 2);
        }
        return items->Get(count - 1);
    }

    virtual T Get(int index) const override {
        if (index < 0) {
            throw MyException(ErrorType::OutOfRange, 0);
        }
        if (index >= count) {
            throw MyException(ErrorType::OutOfRange, 1);
        }
        return items->Get(index);
    }

    virtual int GetLength() const override {
        return count;
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0) {
            throw MyException(ErrorType::OutOfRange, 0); // code=0 => "index < 0?"
        }
        if (endIndex < 0 || startIndex > endIndex || endIndex >= count) {
            throw MyException(ErrorType::OutOfRange, 1); // code=1 => "index >= size"
        }
        int newLen = endIndex - startIndex + 1;
        T* temp = new T[newLen];
        for (int i = 0; i < newLen; i++) {
            temp[i] = items->Get(startIndex + i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(temp, newLen);
        delete[] temp;
        return result;
    }

    virtual Sequence<T>* Append(const T& item) override {
        if (count == capacity) {
            int newCap = capacity * 2;
            items->Resize(newCap);
            capacity = newCap;
        }
        items->Set(count, item);
        count++;
        return this;
    }

    virtual Sequence<T>* Prepend(const T& item) override {
        if (count == capacity) {
            int newCap = capacity * 2;
            items->Resize(newCap);
            capacity = newCap;
        }
        for (int i = count; i > 0; i--) {
            items->Set(i, items->Get(i - 1));
        }
        items->Set(0, item);
        count++;
        return this;
    }

    virtual Sequence<T>* InsertAt(const T& item, int index) override {
        if (index < 0) {
            throw MyException(ErrorType::OutOfRange, 0);
        }
        if (index >= count) {
            throw MyException(ErrorType::OutOfRange, 1);
        }
        if (count == capacity) {
            int newCap = capacity * 2;
            items->Resize(newCap);
            capacity = newCap;
        }
        for (int i = count; i > index; i--) {
            items->Set(i, items->Get(i - 1));
        }
        items->Set(index, item);
        count++;
        return this;
    }

    virtual Sequence<T>* Concat(const Sequence<T>* seq) const override {
        ArraySequence<T>* newSeq = new ArraySequence<T>(*this);
        for (int i = 0; i < seq->GetLength(); i++) {
            newSeq->Append(seq->Get(i));
        }
        return newSeq;
    }

    virtual Sequence<T>* Clone() const override {
        return new ArraySequence<T>(*this);
    }
};
