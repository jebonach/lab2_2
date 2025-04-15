#pragma once
#include <stdexcept>
#include <initializer_list>
#include "how_to_train_your_exception.h"

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int length;

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(T* items, int count) : LinkedList() {
        // if (size < 0) {
        //     throw MyException(ErrorType::OutOfRange, 3);
        // }
        for (int i = 0; i < count; i++) {
            Append(items[i]);
        }
    }

    LinkedList(std::initializer_list<T> list) : LinkedList() {
        for (auto& element : list) {
            Append(element);
        }
    }

    LinkedList(const LinkedList<T>& other) : LinkedList() {
        Node* current = other.head;
        while (current) {
            Append(current->data);
            current = current->next;
        }
    }

    ~LinkedList() {
        Clear();
    }

    void Clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        length = 0;
    }

    T GetFirst() const {
        if (length == 0) {
            throw MyException(ErrorType::OutOfRange, 3);
        }
        return head->data;
    }

    T GetLast() const {
        if (length == 0) {
            throw MyException(ErrorType::OutOfRange, 3);
        }
        return tail->data;
    }

    T Get(int index) const {
        if (index < 0) {
            throw MyException(ErrorType::OutOfRange, 0);
        }
        if (index >= length) {
            throw MyException(ErrorType::OutOfRange, 1);
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0) {
            throw MyException(ErrorType::OutOfRange, 0);
        }
        if (endIndex < 0 || startIndex >= length || endIndex >= length || startIndex > endIndex) {
            throw MyException(ErrorType::OutOfRange, 1);
        }
        LinkedList<T>* subList = new LinkedList<T>();
        Node* current = head;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        }
        for (int i = startIndex; i <= endIndex; i++) {
            subList->Append(current->data);
            current = current->next;
        }
        return subList;
    }

    int GetLength() const {
        return length;
    }

    void Append(const T& item) {
        Node* newNode = new Node(item);
        if (length == 0) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void RemoveAt(int index) {
        if (index < 0) {
            throw MyException(ErrorType::OutOfRange, 2);
        }
        if (index >= length) {
            throw MyException(ErrorType::OutOfRange, 3);
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            length--;
            if (length == 0) {
                tail = nullptr;
            }
            return;
        }
        Node* current = head;
        for (int i=0; i<index-1; i++) {
            current = current->next;
        }
        Node* toDel = current->next;
        current->next = toDel->next;
        delete toDel;
        length--;
        if (index == length) { 
            tail = current;
        }
    }
    
    void Prepend(const T& item) {
        Node* newNode = new Node(item);
        if (length == 0) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    void InsertAt(const T& item, int index) {
        if (index < 0) {
            throw MyException(ErrorType::OutOfRange, 0);
        }
        if (index >= length) {
            throw MyException(ErrorType::OutOfRange, 1);
        }
        if (index == 0) {
            Prepend(item);
            return;
        } else if (index == length) {
            Append(item);
            return;
        }

        Node* newNode = new Node(item);

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        length++;
    }

    LinkedList<T>* Concat(LinkedList<T>* list) {
        if (!list || list->length == 0) {
            return this;
        }
        if (this->length == 0) {
            this->head = list->head;
            this->tail = list->tail;
            this->length = list->length;
        } else {
            this->tail->next = list->head;
            this->tail = list->tail;
            this->length += list->length;
        }
        
        list->head = nullptr;
        list->tail = nullptr;
        list->length = 0;

        return this;
    }
    
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            Clear();
            Node* current = other.head;
            while (current) {
                Append(current->data);
                current = current->next;
            }
        }
        return *this;
    }
};
