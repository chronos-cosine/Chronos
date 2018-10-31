/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConcurrentBag.h
 * Author: user
 *
 * Created on 12 October 2018, 6:43 AM
 */

#ifndef COLLECTIONS_CONCURRENTQUEUE_H
#define COLLECTIONS_CONCURRENTQUEUE_H

#include "Collections/ICollection.h"
#include <condition_variable>
#include <mutex>
#include <queue>

namespace Collections {

    template <typename T>
    class ConcurrentQueue : public ICollection<T> {
        ConcurrentQueue(const ConcurrentQueue&) = delete;
        ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
    private:
        std::queue<T> __queue;
    public:
        virtual ~ConcurrentQueue();
        ConcurrentQueue();
        
        virtual void push(T item);
        virtual T pop();
        virtual bool empty();
        typename std::queue<T>::size_type size() const;
        
    }; /* class ConcurrentQueue */
    
    template <typename T>
    ConcurrentQueue<T>::~ConcurrentQueue() { } /* ~ConcurrentQueue() */
    
    template <typename T>
    ConcurrentQueue<T>::ConcurrentQueue() { } /* ConcurrentQueue() */
    
    template <typename T>
    void 
    ConcurrentQueue<T>::push(T item) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __queue.push(std::move(item));
        __condition_variable.notify_one();
    } /* void ConcurrentQueue<T>::push(T) */
    
    template <typename T>
    T 
    ConcurrentQueue<T>::pop() {
        std::unique_lock<std::mutex> lock(__mutex);
        
        __condition_variable.wait(lock, [this] { return !__queue.empty(); });
        
        T item = std::move(__queue.front());
        __queue.pop();
        
        return item;
    } /* T ConcurrentQueue<T>::pop() */
    
    template <typename T>
    bool 
    ConcurrentQueue<T>::empty() {
        return __queue.empty();
    } /* bool empty() */
    
    template <typename T>
    typename std::queue<T>::size_type 
    ConcurrentQueue<T>::size() const {
        return __queue.size();
    } /* std::queue<T>::size_type ConcurrentQueue<T>::size() */
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTQUEUE_H */

