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

#include <condition_variable>
#include <mutex>
#include <queue>

namespace Collections {

    template <typename T>
    class ConcurrentQueue {
    private:
        std::queue<T> __queue;
        std::mutex __mutex;
        std::condition_variable __condition_variable;
    public:
        ConcurrentQueue();
        virtual ~ConcurrentQueue();
        
        void push(T item);
        T pop();
        typename std::queue<T>::size_type size() const;
    public:
        ConcurrentQueue(const ConcurrentQueue&) = delete;
        ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
        ConcurrentQueue(ConcurrentQueue&&) = delete;
        ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;
    };
    
    template <typename T>
    ConcurrentQueue<T>::ConcurrentQueue() { }
    
    template <typename T>
    ConcurrentQueue<T>::~ConcurrentQueue() { }
    
    template <typename T>
    void 
    ConcurrentQueue<T>::push(T item) {
        std::lock_guard<std::mutex> lock(__mutex);
        __queue.push(std::move(item));
        __condition_variable.notify_one();
    }
    
    template <typename T>
    T 
    ConcurrentQueue<T>::pop() {
        std::unique_lock<std::mutex> lock(__mutex);
        __condition_variable.wait(lock, [this] { return !__queue.empty(); });
        T item = std::move(__queue.front());
        __queue.pop();
        
        return item;
    }
    
    template <typename T>
    typename std::queue<T>::size_type 
    ConcurrentQueue<T>::size() const {
        return __queue.size();
    }
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTQUEUE_H */

