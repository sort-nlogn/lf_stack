#pragma once
#include <atomic>

template<class T>
class LockFreeStack{
    private:
        std::atomic<int> capacity;
        std::atomic<T *>head;
        T *data, *end;
    public:
        LockFreeStack(int capacity);

        void push(T value);

        T pop();

        bool is_empty();

        void clear();
};