#pragma once
#include <stdexcept>

template <class T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>* seq) const = 0;

    virtual Sequence<T>* RemoveAt(int index) = 0;
    virtual const char* TypeName() const = 0;

    virtual Sequence<T>* Clone() const = 0;
    virtual ~Sequence() {}
};
