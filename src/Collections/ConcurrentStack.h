/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConcurrentStack.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 26 October 2018, 8:03 PM
 */

#ifndef COLLECTIONS_CONCURRENTSTACK_H
#define COLLECTIONS_CONCURRENTSTACK_H

#include <condition_variable>
#include <mutex>
#include <stack>

namespace Collections {

    template <typename T>
    class ConcurrentStack {
    private:
        std::stack<T> __stack;
        std::condition_variable __condition_variable;
        std::mutex __mutex;
    public:
        virtual ~ConcurrentStack();
        ConcurrentStack();
        ConcurrentStack(const ConcurrentStack&) = delete;
        ConcurrentStack& operator=(const ConcurrentStack&) = delete;
        
        void push(T item);
        T pop();
        typename std::queue<T>::size_type size() const;
    };
    
    template <typename T>
    ConcurrentStack<T>::~ConcurrentStack() { }
    
    template <typename T>
    ConcurrentStack<T>::ConcurrentStack() { }
    
    template <typename T>
    void 
    ConcurrentStack<T>::push(T item) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __stack.push(std::move(item));
        __condition_variable.notify_one();
    }
    
    template <typename T>
    T 
    ConcurrentStack<T>::pop() {
        std::unique_lock<std::mutex> lock(__base_mutex);
        
        __condition_variable.wait(lock, [this] { return !__stack.empty(); });
        
        T item = std::move(__stack.top());
        __stack.pop();
        
        return item;
    }
    
    template <typename T>
    typename std::stack<T>::size_type 
    ConcurrentStack<T>::size() const {
        return __stack.size();
    }
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTSTACK_H */

