#pragma once
#include "Queue.h"
#include "DynamicArray.h"
#include <functional>

template<class T,class Cmp=std::less<T>>
class PQueueArray : public Queue<T> {

};