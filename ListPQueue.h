#pragma once
#include "Queue.h"
#include "LinkedList.h"
#include <functional>

template<class T,class Cmp=std::less<T>>
class PQueueList : public Queue<T> {

};