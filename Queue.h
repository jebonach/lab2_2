#pragma once
#include <cstddef>

template<class T>
class Queue {
public:

    virtual void Enqueue(const T& item) = 0;
    virtual T Dequeue() = 0;

    virtual T& GetFront() = 0;
    virtual const T& GetFront() const = 0;

    virtual T& GetRear() = 0;
    virtual const T& GetRear() const = 0;

    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual std::size_t Size() const = 0;
    virtual void Clear() = 0;

    virtual Queue<T>* Concat(const Queue<T>& other) const = 0;
    virtual Queue<T>* Subqueue(std::size_t start, std::size_t end) const = 0;
    // virtual bool ContainsSubqueue() const = 0;
    // virtual std::pair<Queue<T>*, Queue<T>*> Split() const = 0;

    // virtual Queue<T>* Where() const = 0;
    // virtual Queue<T>* Map() const = 0;
    // virtual T Reduce() const = 0;

    virtual ~Queue() = default;
    virtual const char* TypeName() const = 0;
    virtual Queue<T>* Clone() const = 0;
};

class Student {
    public:
        std::string name;
        int age;
        double gpa;
    
        Student() : name(""), age(0), gpa(0.0) {}
        Student(std::string name, int age, double gpa)
            : name(std::move(name)), age(age), gpa(gpa) {}
    
        friend std::ostream& operator<<(std::ostream& os, const Student& s) {
            return os << "Student(name=" << s.name << ", age=" << s.age << ", GPA=" << s.gpa << ")";
        }
        bool operator==(const Student& other) const {
            return name == other.name && age == other.age && gpa == other.gpa;
        }
    };