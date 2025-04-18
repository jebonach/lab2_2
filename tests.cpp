#include <iostream>
#include <cassert>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"

template<class Seq>
void checkEqual(const Seq* seq, std::initializer_list<int> ref)
{
    assert(seq->GetLength() == static_cast<int>(ref.size()));
    int i = 0;
    for (int v : ref) {
        assert(seq->Get(i) == v);
        ++i;
    }
}

void TestDynamicArray() {
    int arr[] = {1, 2, 3};
    DynamicArray<int> d(arr, 3);
    assert(d.GetSize() == 3);
    assert(d.Get(0) == 1);
    assert(d.Get(1) == 2);
    assert(d.Get(2) == 3);

    d.Resize(5);
    assert(d.GetSize() == 5);
    d.Set(3, 10);
    d.Set(4, 20);
    assert(d.Get(3) == 10);
    assert(d.Get(4) == 20);
}

void TestLinkedList() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Prepend(5);
    assert(list.GetLength() == 3);
    assert(list.Get(0) == 5);
    assert(list.Get(1) == 10);
    assert(list.Get(2) == 20);

    auto* sub = list.GetSubList(0, 1);
    assert(sub->GetLength() == 2);
    assert(sub->Get(0) == 5);
    assert(sub->Get(1) == 10);
    delete sub;
}

void TestArraySequence() {
    ArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Prepend(0);
    assert(seq.Get(0) == 0);
    assert(seq.Get(1) == 1);

    seq.InsertAt(999, 2);
    assert(seq.Get(2) == 999);
    assert(seq.Get(3) == 2);

    Sequence<int>* sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    assert(sub->Get(1) == 999);
    assert(sub->Get(2) == 2);
    delete sub;
}

void TestListSequence() {
    ListSequence<int> seq;
    seq.Append(1)->Append(2)->Append(3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Prepend(0);
    assert(seq.Get(0) == 0);
    assert(seq.Get(1) == 1);

    seq.InsertAt(999, 2);
    assert(seq.Get(2) == 999);
    assert(seq.Get(3) == 2);

    auto* sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    assert(sub->Get(1) == 999);
    assert(sub->Get(2) == 2);
    delete sub;
}

template<class Seq>
void ReverseScenarios(const char* tag)
{
    std::cout << "  Reverse‑block for " << tag << '\n';

    // 1) empty
    {
        Seq s;
        s.reverse();
        checkEqual(&s,{});
    }
    // 2) single element
    {
        Seq s;  s.Append(42);
        s.reverse();
        checkEqual(&s,{42});
    }
    // 3) two elements
    {
        Seq s;  s.Append(7)->Append(9);
        s.reverse();
        checkEqual(&s,{9,7});
    }
    // 4) odd count
    {
        Seq s; for (int v:{1,2,3,4,5}) s.Append(v);
        s.reverse();
        checkEqual(&s,{5,4,3,2,1});
    }
    // 5) even count
    {
        Seq s; for (int v:{10,20,30,40}) s.Append(v);
        s.reverse();
        checkEqual(&s,{40,30,20,10});
    }
}

int main() {
    std::cout << "Running tests..." << std::endl;
    TestDynamicArray();
    TestLinkedList();
    TestArraySequence();
    TestListSequence();
    ReverseScenarios<ListSequence<int>> ("ListSequence");
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
