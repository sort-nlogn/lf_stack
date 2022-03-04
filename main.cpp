#include <iostream>
#include <thread>
#include <atomic>
#include <thread>
#include "LockFreeStack.hpp"
#include "LockFreeStack.cpp"

using namespace std;

template<class T>
void push(LockFreeStack<T> &s){
    for(int i = 1; i < 101; i++){
        s.push(i);
        cout << "Push: " << i << endl;
    }
}

template<class T>
void pop(LockFreeStack<T> &s){
    for(int i = 0; i < 100; i++){
        this_thread::sleep_for(chrono::milliseconds(1));
        if(!s.is_empty()){
            cout <<"Pop: " <<  s.pop() << endl;
        }
    }
}

int main(int argc, char *argv[]){
    LockFreeStack<int> s(100); 

    thread push_thread(push<int>, ref(s));
    thread pop_thread(pop<int>, ref(s));

    push_thread.join();
    pop_thread.join();

    return 0;
}
