#include "LockFreeStack.hpp"
#include <atomic>
#include <iostream>
#include <stdexcept>

template<class T>
LockFreeStack<T>::LockFreeStack(int capacity){
    if(capacity <= 0)
        throw std::runtime_error("Incorrect capacity value!");

    this->capacity.store(capacity, std::memory_order_relaxed);
    data = new T[capacity + 1];
    end = data + capacity;
    head.store(data, std::memory_order_relaxed);
}

template<class T>
void LockFreeStack<T>::push(T value){
    T *new_head = head.load(std::memory_order_acquire) + 1;
    if(head == end)
        throw std::runtime_error("Stack overflow!");
    T *curr_head = new_head - 1;

    while(!head.compare_exchange_weak(curr_head, new_head,
                                      std::memory_order_acquire,
                                      std::memory_order_release));
    *curr_head = value;
}

template<class T>
T LockFreeStack<T>::pop(){
    T *curr_head = head.load(std::memory_order_acquire);
    if(curr_head == data)
        throw std::runtime_error("Stack underflow!");
    T *new_head = curr_head - 1;

    while(!head.compare_exchange_weak(curr_head, new_head,
                                      std::memory_order_acquire,
                                      std::memory_order_release)); 
    return *(curr_head - 1);
}

template<class T>
bool LockFreeStack<T>::is_empty(){
    return (head.load(std::memory_order_acquire) == data);
}

template<class T>
void LockFreeStack<T>::clear(){
    while(!is_empty()){
        pop();
    }
}

