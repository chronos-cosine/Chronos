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

#ifndef CORE_CONCURRENTQUEUE_H
#define CORE_CONCURRENTQUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace Core {

    template <typename T>
    class ConcurrentQueue {
    public:
        ConcurrentQueue(const ConcurrentQueue&) = delete;
        ConcurrentQueue& operator=(ConcurrentQueue&) = delete;
    public:
        ConcurrentQueue();
        ConcurrentQueue(ConcurrentQueue&& move);
        virtual ~ConcurrentQueue();
        
        void push(T item);
        T pop();
        
        virtual ConcurrentQueue& operator=(ConcurrentQueue&& move);
    private:
        std::queue<T> __queue;
        std::mutex __mutex;
        std::condition_variable __condition_variable;
    };
    
    template <typename T>
    ConcurrentQueue<T>::ConcurrentQueue() { }
    
    template <typename T>
    ConcurrentQueue<T>::ConcurrentQueue(ConcurrentQueue&& move) 
            : __mutex(std::move(move.__mutex)), __queue(std::move(move.__queue)), 
              __condition_variable(std::move(move.__condition_variable)) { }
    
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
    ConcurrentQueue::pop() {
        std::unique_lock<std::mutex> lock(__mutex);
        __condition_variable.wait(lock, [this] { return !__queue.empty(); });
        T item = std::move(__queue.front());
        __queue.pop();
        
        return item;
    }
        
    template <typename T>
    ConcurrentQueue& 
    ConcurrentQueue<T>::operator=(ConcurrentQueue&& move) { 
        __mutex = std::move(move.__mutex);
        __queue = std::move(move.__queue); 
        __condition_variable = std::move(move.__condition_variable);
        
        return *this;
    }

} /* namespace Core

#endif /* CORE_CONCURRENTQUEUE_H */

