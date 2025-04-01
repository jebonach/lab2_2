#pragma once
#include <stdexcept>

template <class T>
class DynamicArray {
private:
    T* data;
    int size;

public:
    DynamicArray(const T* items, int count) {
        if (count < 0) {
            throw std::out_of_range("DynamicArray: count < 0");
        }
        size = count;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = items[i];
        }
    }

    DynamicArray(int size) {
        if (size < 0) {
            throw std::out_of_range("DynamicArray: size < 0");
        }
        this->size = size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = T();
        }
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

    int GetSize() const {
        return size;
    }

    T Get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::Get out of range");
        }
        return data[index];
    }

    void Set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::Set out of range");
        }
        data[index] = value;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::out_of_range("DynamicArray::Resize newSize < 0");
        }
        T* newData = new T[newSize];
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; i++) {
            newData[i] = data[i];
        }
        for (int i = minSize; i < newSize; i++) {
            newData[i] = T();
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
            throw std::out_of_range("DynamicArray::operator[] out of range");
        }
        return data[index];
    }
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("DynamicArray::operator[] out of range");
        }
        return data[index];
    }
};
