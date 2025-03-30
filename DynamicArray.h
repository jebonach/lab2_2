#pragma once
#include <stdexcept>
#include <initializer_list>

template <class T>
class DynamicArray {
private:
    T* data;
    int size;

public:
    DynamicArray(T* items, int count) {
        if (count < 0) {
            throw std::out_of_range("DynamicArray::count < 0");
        }
        size = count;
        data = new T[count];
        for (int i = 0; i < count; i++) {
            data[i] = items[i];
        }
    }

    DynamicArray(std::initializer_list<T> list)
        : DynamicArray(list.size() ? const_cast<T*>(list.begin()) : nullptr,
                       static_cast<int>(list.size())) {
    }

    DynamicArray(int size) {
        if (size < 0) {
            throw std::out_of_range("DynamicArray::size < 0");
        }
        this->size = size;
        data = new T[size];
    }

    DynamicArray(const DynamicArray<T>& other) {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    ~DynamicArray() {
        delete[] data;
    }

    T Get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::Get() index out of range(unluck)");
        }
        return data[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::Set() index out of range(unluck)");
        }
        data[index] = value;
    }

    int GetSize() const {
        return size;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::out_of_range("DynamicArray::Resize() newSize < 0");
        }
        T* newData = new T[newSize];
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::operator[] index out of range(unluck)");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::operator[] index out of range(unluck)");
        }
        return data[index];
    }
};
