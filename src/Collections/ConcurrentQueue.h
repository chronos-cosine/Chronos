/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Collections/ConcurrentQueue.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 12 October 2018, 10:52 PM
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
    ConcurrentQueue<T>::~ConcurrentQueue() { }
    
    template <typename T>
    ConcurrentQueue<T>::ConcurrentQueue() { } 
    
    template <typename T>
    void 
    ConcurrentQueue<T>::push(T item) {
        std::lock_guard<std::mutex> lock(ICollection<T>::__mutex);
        
        __queue.push(std::move(item));
        ICollection<T>::__condition_variable.notify_one();
    } 
    
    template <typename T>
    T 
    ConcurrentQueue<T>::pop() {
        std::unique_lock<std::mutex> lock(ICollection<T>::__mutex);
        
        ICollection<T>::__condition_variable.wait(lock, [this] { 
            return !__queue.empty(); 
        });
        
        T item = std::move(__queue.front());
        __queue.pop();
        
        return item;
    } 
    
    template <typename T>
    bool 
    ConcurrentQueue<T>::empty() {
        return __queue.empty();
    } 
    
    template <typename T>
    typename std::queue<T>::size_type 
    ConcurrentQueue<T>::size() const {
        return __queue.size();
    } 
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTQUEUE_H */

