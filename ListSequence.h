#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;

public:
    ListSequence() {
        list = new LinkedList<T>();
    }

    ListSequence(T* arr, int count) {
        list = new LinkedList<T>(arr, count);
    }

    ListSequence(std::initializer_list<T> initList) {
        list = new LinkedList<T>(initList);
    }

    ListSequence(const ListSequence<T>& other) {
        list = new LinkedList<T>(*other.list);
    }

    virtual ~ListSequence() {
        delete list;
    }

    virtual T GetFirst() const override {
        return list->GetFirst();
    }

    virtual T GetLast() const override {
        return list->GetLast();
    }

    virtual T Get(int index) const override {
        return list->Get(index);
    }

    virtual int GetLength() const override {
        return list->GetLength();
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 ) {
            throw MyException(ErrorType::OutOfRange, 0);
        }
        if (startIndex > endIndex || endIndex >= list->GetLength()) {
            throw MyException(ErrorType::OutOfRange, 1);
        }
        LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
        ListSequence<T>* result = new ListSequence<T>();
        delete result->list; 
        result->list = subList;
        return result;
    }

    virtual Sequence<T>* Append(const T& item) override {
        list->Append(item);
        return this;
    }

    virtual Sequence<T>* RemoveAt(int index) override {
        list->RemoveAt(index);
        return this;
    }    

    virtual const char* TypeName() const override {
        return "ListSequence";
    }

    virtual Sequence<T>* Prepend(const T& item) override {
        list->Prepend(item);
        return this;
    }

    virtual Sequence<T>* InsertAt(const T& item, int index) override {
        list->InsertAt(item, index);
        return this;
    }

    virtual Sequence<T>* Concat(const Sequence<T>* seq) const override {
        const ListSequence<T>* listSeq = dynamic_cast<const ListSequence<T>*>(seq);
        ListSequence<T>* result = new ListSequence<T>(*this);
        for (int i = 0; i < seq->GetLength(); i++) {
            result->Append(seq->Get(i));
        }
        return result;
    }
        // if (listSeq) {
        //     LinkedList<T>* concatList = list->Concat(listSeq->list);
        //     ListSequence<T>* result = new ListSequence<T>();
        //     delete result->list;
        //     result->list = concatList;
        //     return result;conca
        // } else {
        //     ListSequence<T>* result = new ListSequence<T>(*this);
        //     for (int i = 0; i < seq->GetLength(); i++) {
        //         result->Append(seq->Get(i));
        //     }
        //     return result;
        // }
    void reverse() {
        list->reverse();
    }
        
    virtual Sequence<T>* Clone() const override {
        return new ListSequence<T>(*this);
    }
};
