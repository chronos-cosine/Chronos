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

#include "Collections/ICollection.h"
#include <condition_variable>
#include <mutex>
#include <stack>

namespace Collections {

    template <typename T>
    class ConcurrentStack : public ICollection<T> {
        ConcurrentStack(const ConcurrentStack&) = delete;
        ConcurrentStack& operator=(const ConcurrentStack&) = delete;
    private:
        std::stack<T> __stack;
    public:
        virtual ~ConcurrentStack();
        ConcurrentStack();
        
        virtual void push(T item);
        virtual T pop();
        virtual bool empty();
        typename std::stack<T>::size_type size() const;
    }; /* class ConcurrentStack */
    
    template <typename T>
    ConcurrentStack<T>::~ConcurrentStack() { } /* ~ConcurrentStack() */
    
    template <typename T>
    ConcurrentStack<T>::ConcurrentStack() { } /* ConcurrentStack() */
    
    template <typename T>
    void 
    ConcurrentStack<T>::push(T item) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __stack.push(std::move(item));
        __condition_variable.notify_one();
    } /* void ConcurrentStack<T>::push(T) */
    
    template <typename T>
    T 
    ConcurrentStack<T>::pop() {
        std::unique_lock<std::mutex> lock(__mutex);
        
        __condition_variable.wait(lock, [this] { return !__stack.empty(); });
        T item = std::move(__stack.top());
        __stack.pop();
        
        return item;
    } /* T ConcurrentStack<T>::pop() */
    
    template <typename T>
    bool 
    ConcurrentQueue<T>::empty() {
        return __stack.empty();
    } /* bool empty() */
    
    template <typename T>
    typename std::stack<T>::size_type 
    ConcurrentStack<T>::size() const {
        return __stack.size();
    } /* std::stack<T>::size_type ConcurrentStack<T>::size() */
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTSTACK_H */

