#pragma once
#include <utility>
#include "ArraySequence.h"


template <class T, class R>
Sequence<R>* map() { }


template <class T>
Sequence<T>* where() { }


template <class T>
T reduce(const Sequence<T>* seq, std::function<T() ){ }


template <class T1, class T2>
Sequence<std::pair<T1, T2>>* zip() {
}


template <class T1, class T2>
std::pair<Sequence<T1>*, Sequence<T2>*> unzip() { }
