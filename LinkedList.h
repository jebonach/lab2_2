#pragma once
#include <stdexcept>
#include <initializer_list>

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
        if (count < 0) {
            throw std::out_of_range("LinkedList::count < 0");
        }
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
            throw std::out_of_range("LinkedList::GetFirst() - list is empty(upset)");
        }
        return head->data;
    }

    T GetLast() const {
        if (length == 0) {
            throw std::out_of_range("LinkedList::GetLast() - list is empty(upset)");
        }
        return tail->data;
    }

    T Get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("LinkedList::Get() - index out of range(unluck)");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex >= length || endIndex >= length || startIndex > endIndex) {
            throw std::out_of_range("LinkedList::GetSubList() - index out of range(unluck)");
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
        if (index < 0 || index > length) {
            throw std::out_of_range("LinkedList::InsertAt() - index out of range(unluck)");
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
